// ============================================================================
// Player-facing L-button menu for the four QoL tools (stat editor, nature
// changer, Hidden Power changer, move editor).
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
// Currently ungated, per instructions - the four tools are meant to be
// freely available before "the facility" exists. GATE HERE LATER: once a
// facility run can be in progress, the team is locked for the run's
// duration, and an editor able to rewrite it mid-run would break that lock.
// Add the "no run in progress" check at the very top of ShowLMenu() below
// (return immediately, without building the menu, if a run is active) -
// that's the single choke point every path to this menu goes through.
// ============================================================================

#include "global.h"
#include "event_object_lock.h"
#include "event_object_movement.h"
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
extern const u8 Debug_EventScript_OpenMoveEditor[];

enum LMenuAction
{
    LMENU_ACTION_STAT_EDITOR,
    LMENU_ACTION_CHANGE_NATURE,
    LMENU_ACTION_CHANGE_HP_TYPE,
    LMENU_ACTION_MOVE_EDITOR,
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
static const u8 sLMenuText_MoveEditor[] = _("Move Editor");
static const u8 sLMenuText_Cancel[] = _("Cancel");

static const struct LMenuOption sLMenuOptions[LMENU_ACTION_COUNT] =
{
    [LMENU_ACTION_STAT_EDITOR]    = { sLMenuText_StatEditor,   Debug_EventScript_OpenStatEditor },
    [LMENU_ACTION_CHANGE_NATURE]  = { sLMenuText_ChangeNature, Debug_EventScript_ChangeMonNature },
    [LMENU_ACTION_CHANGE_HP_TYPE] = { sLMenuText_ChangeHPType, Debug_EventScript_ChangeMonHPType },
    [LMENU_ACTION_MOVE_EDITOR]    = { sLMenuText_MoveEditor,   Debug_EventScript_OpenMoveEditor },
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

    // GATE HERE LATER - see the file header comment.

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

static void CloseLMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].tMenuTaskId, NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);
    DestroyTask(taskId);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
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
            ScriptContext_SetupScript(script);
        }
        else
        {
            CloseLMenu(taskId);
            ScriptContext_Enable();
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        CloseLMenu(taskId);
        ScriptContext_Enable();
    }
}
