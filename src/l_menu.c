// ============================================================================
// Player-facing L-button menu for the seven QoL tools (stat editor, nature
// changer, Hidden Power changer, level-up move relearner, egg move
// relearner, ability switcher, teach TM).
//
// Structured after Emerald Imperium's L-menu as a reference for how the menu
// is registered and opened (iriv24/pokeemerald-expansion, release branch):
//   - src/field_control_avatar.c there adds a pressedLButton bit to
//     struct FieldInput, sets it on L_BUTTON in FieldGetPlayerInput(), and
//     checks it in the input dispatch (ProcessPlayerFieldInput() there) to
//     call ShowLMenu() - exactly the same three-step wiring is added to our
//     own src/field_control_avatar.c in this change (reusing the existing,
//     previously-unused input_field_1_1 bit rather than adding a new one).
//   - Imperium's own src/l_menu.c is a ~1000-line reimplementation of the
//     whole Start Menu (PC, DexNav, time changer, repel/auto-run/follower
//     toggles, stat editor, etc.) - far more than the four tools this menu
//     needs. Rather than port that, this is a small purpose-built menu using
//     this checkout's own generic small-list-menu idiom - the same one
//     src/debug.c's basic menu type uses (LoadMessageBoxAndBorderGfx() + a
//     WindowTemplate + ListMenuInit() + an input task, no BG swap, drawn as
//     an overlay over the still-visible overworld, the same way the vanilla
//     Start Menu and the debug menu both work) - and the freeze/lock-on-open,
//     unfreeze/unlock-on-close pair is taken from src/start_menu.c
//     (ShowStartMenu()/its close paths), the more thoroughly-proven pattern
//     for a genuinely player-facing overworld menu.
//
// Gated on IsFacilityRunActive() (src/facility.c) - see run-loop-spec.md's
// "Mid-run access restrictions". The team is locked for the run's duration,
// and an editor able to rewrite it mid-run would break that lock. ShowLMenu()
// is the single choke point every path to this menu goes through, so that's
// the only place this needs checking.
// ============================================================================

#include "global.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
#include "facility.h"
#include "field_player_avatar.h"
#include "list_menu.h"
#include "l_menu.h"
#include "main.h"
#include "menu.h"
#include "map_name_popup.h"
#include "overworld.h"
#include "script.h"
#include "sound.h"
#include "task.h"
#include "window.h"
#include "constants/songs.h"

// These live in data/scripts/debug.inc, already used by the debug menu
// (src/debug.c) - reused here rather than duplicated.
extern const u8 Debug_EventScript_OpenStatEditor[];
extern const u8 Debug_EventScript_ChangeMonNature[];
extern const u8 Debug_EventScript_ChangeMonHPType[];
extern const u8 Debug_EventScript_RelearnLevelUpMove[];
extern const u8 Debug_EventScript_RelearnEggMove[];
extern const u8 Debug_EventScript_SetAbility[];
extern const u8 Debug_EventScript_TeachTM[];

// The Move Editor slot used to run a custom "full legal movepool" relearn
// state and repeatedly corrupted the heap (see data/scripts/debug.inc's
// comment on Debug_EventScript_RelearnLevelUpMove for the full history).
// Retired in favor of the plain level-up relearner plus a "Teach TM" tool
// (Debug_EventScript_TeachTM) that teaches straight from the 166-move TM
// list without touching the bag - see the comment on
// GiveFrontierStartingGrants() in src/new_game.c for why TMs aren't bag
// items here. Between the two the player can still reach any legal move.
enum LMenuAction
{
    LMENU_ACTION_STAT_EDITOR,
    LMENU_ACTION_CHANGE_NATURE,
    LMENU_ACTION_CHANGE_HP_TYPE,
    LMENU_ACTION_RELEARN_MOVE,
    LMENU_ACTION_EGG_MOVE,
    LMENU_ACTION_SWITCH_ABILITY,
    LMENU_ACTION_TEACH_TM,
    LMENU_ACTION_COUNT,
};

struct LMenuOption
{
    const u8 *label;
    const u8 *script;
};

static void Task_LMenuHandleInput(u8 taskId);

#define LMENU_WIDTH 17

static const struct WindowTemplate sLMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = LMENU_WIDTH,
    .height = 2 * (LMENU_ACTION_COUNT + 1), // +1 for Cancel
    .paletteNum = 15,
    .baseBlock = 1,
};

static const u8 sLMenuText_StatEditor[] = _("Stat Editor");
static const u8 sLMenuText_ChangeNature[] = _("Change Nature");
static const u8 sLMenuText_ChangeHPType[] = _("Change Hidden Power");
static const u8 sLMenuText_RelearnMove[] = _("Relearn Move");
static const u8 sLMenuText_EggMove[] = _("Learn Egg Move");
static const u8 sLMenuText_SwitchAbility[] = _("Switch Ability");
static const u8 sLMenuText_TeachTM[] = _("Teach TM");
static const u8 sLMenuText_Cancel[] = _("Cancel");

static const struct LMenuOption sLMenuOptions[LMENU_ACTION_COUNT] =
{
    [LMENU_ACTION_STAT_EDITOR]     = { sLMenuText_StatEditor,    Debug_EventScript_OpenStatEditor },
    [LMENU_ACTION_CHANGE_NATURE]   = { sLMenuText_ChangeNature,  Debug_EventScript_ChangeMonNature },
    [LMENU_ACTION_CHANGE_HP_TYPE]  = { sLMenuText_ChangeHPType,  Debug_EventScript_ChangeMonHPType },
    [LMENU_ACTION_RELEARN_MOVE]    = { sLMenuText_RelearnMove,   Debug_EventScript_RelearnLevelUpMove },
    [LMENU_ACTION_EGG_MOVE]        = { sLMenuText_EggMove,       Debug_EventScript_RelearnEggMove },
    [LMENU_ACTION_SWITCH_ABILITY]  = { sLMenuText_SwitchAbility, Debug_EventScript_SetAbility },
    [LMENU_ACTION_TEACH_TM]        = { sLMenuText_TeachTM,       Debug_EventScript_TeachTM },
};

static EWRAM_DATA struct ListMenuItem sLMenuItems[LMENU_ACTION_COUNT + 1] = {0};

#define tMenuTaskId data[0]
#define tWindowId   data[1]

void ShowLMenu(void)
{
    struct ListMenuTemplate menuTemplate = {0};
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;
    u32 i;

    // Blocked for the duration of a facility run - re-tuning EVs/moveset or
    // nature/Hidden Power against the team you're about to fight isn't a
    // locked team. See run-loop-spec.md's "Mid-run access restrictions".
    if (IsFacilityRunActive())
        return;

    for (i = 0; i < LMENU_ACTION_COUNT; i++)
    {
        sLMenuItems[i].name = sLMenuOptions[i].label;
        sLMenuItems[i].id = i;
    }
    sLMenuItems[LMENU_ACTION_COUNT].name = sLMenuText_Cancel;
    sLMenuItems[LMENU_ACTION_COUNT].id = LMENU_ACTION_COUNT;

    if (!IsOverworldLinkActive())
    {
        FreezeObjectEvents();
        PlayerFreeze();
        StopPlayerAvatar();
    }

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sLMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);
    CopyWindowToVram(windowId, COPYWIN_GFX);

    menuTemplate.items = sLMenuItems;
    menuTemplate.moveCursorFunc = ListMenuDefaultCursorMoveFunc;
    menuTemplate.totalItems = LMENU_ACTION_COUNT + 1;
    menuTemplate.maxShowed = LMENU_ACTION_COUNT + 1;
    menuTemplate.windowId = windowId;
    menuTemplate.header_X = 0;
    menuTemplate.item_X = 8;
    menuTemplate.cursor_X = 0;
    menuTemplate.upText_Y = 1;
    menuTemplate.cursorPal = 2;
    menuTemplate.fillValue = 1;
    menuTemplate.cursorShadowPal = 3;
    menuTemplate.lettersSpacing = 1;
    menuTemplate.itemVerticalPadding = 0;
    menuTemplate.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    menuTemplate.fontId = FONT_NORMAL;
    menuTemplate.cursorKind = 0;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    inputTaskId = CreateTask(Task_LMenuHandleInput, 3);
    gTasks[inputTaskId].tMenuTaskId = menuTaskId;
    gTasks[inputTaskId].tWindowId = windowId;

    CopyWindowToVram(windowId, COPYWIN_FULL);
    LockPlayerFieldControls();
}

// Window/task teardown only - deliberately does NOT touch the freeze/lock
// state ShowLMenu() put in place. The two callers below need opposite things
// there: picking an option hands off to a script that expects the field
// still frozen (its own release/releaseall - see ScrCmd_release(all) in
// src/scrcmd.c - is what's supposed to undo that, exactly like any other
// script), while Cancel has no follow-up script and has to undo the freeze
// itself. Doing the unfreeze here unconditionally (the previous bug) meant
// object events kept moving and animating in the background for the whole
// time a chosen tool's script - and whatever full-screen UI it opened, e.g.
// the move relearner's own CB2 - was up, stomping on state and VRAM that UI
// assumed was quiescent. That's what was corrupting the move editor's
// "replace which move" popup text and, later, whatever it clobbered next.
static void CloseLMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].tMenuTaskId, NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);
    DestroyTask(taskId);
}

static void CancelLMenu(u8 taskId)
{
    CloseLMenu(taskId);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
    ScriptContext_Enable();
}

static void Task_LMenuHandleInput(u8 taskId)
{
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (input < LMENU_ACTION_COUNT)
        {
            const u8 *script = sLMenuOptions[input].script;
            CloseLMenu(taskId);
            // Field stays frozen; ScriptContext_SetupScript() re-locks player
            // controls itself, and the script's own release/releaseall
            // unfreezes object events again once it's done - see the
            // comment on CloseLMenu().
            ScriptContext_SetupScript(script);
        }
        else
        {
            CancelLMenu(taskId);
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        CancelLMenu(taskId);
    }
}
