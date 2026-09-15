#ifndef GUARD_UI_STAT_EDIT_H
#define GUARD_UI_STAT_EDIT_H

#include "main.h"

// Ported from Emerald Imperium (iriv24/pokeemerald-expansion, release branch,
// include/ui_stat_editor.h). Credited in src/data/credits.h.
//
// StatEditor_Init() is unchanged from Imperium. Task_OpenStatEditorFromLMenu()
// was Imperium's L-menu entry point and isn't ported (we have no L-menu);
// StatEditorSpecial() is a new def_special-registered wrapper used to enter
// from a script instead (see data/scripts/debug.inc). Imperium's two dead
// externs (gNatureNamePointers, gAbilityNames — unused by ui_stat_editor.c,
// which reads gNaturesInfo/gAbilitiesInfo instead) were dropped rather than
// ported, since neither symbol exists in this checkout.
void StatEditorSpecial(void);
void StatEditor_Init(MainCallback callback);

#endif // GUARD_UI_STAT_EDIT_H
