#include "DialogEditLeveledCreatureObjectWindow.h"

#include "WinUIUtil.h"

#include "Settings.h"

namespace se::cs::dialog::edit_leveled_creature_object_window {
	constexpr auto MIN_WIDTH = 524u;
	constexpr auto MIN_HEIGHT = 220u;

	// Saving the columns size

	void restoreLeveledCreatureColumnWidths(HWND hWnd) {
		const auto LeveledCreature = GetDlgItem(hWnd, CONTROL_ID_LEVELED_LIST);

		ListView_SetColumnWidth(LeveledCreature, 0, settings.leveled_creature_window.column_PC_Level.width);
		ListView_SetColumnWidth(LeveledCreature, 1, settings.leveled_creature_window.column_Creature_Name.width);
	}

	void saveLeveledCreatureColumnWidths(HWND hWnd) {
		const auto LeveledCreature = GetDlgItem(hWnd, CONTROL_ID_LEVELED_LIST);

		settings.leveled_creature_window.column_PC_Level.width = ListView_GetColumnWidth(LeveledCreature, 0);
		settings.leveled_creature_window.column_Creature_Name.width = ListView_GetColumnWidth(LeveledCreature, 1);
	}

	// Extended window messages

	static std::optional<LRESULT> PatchDialogProc_OverrideResult = {};

	void PatchDialogProc_BeforeDestroy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		saveLeveledCreatureColumnWidths(hWnd);
	}

	std::optional<LRESULT> forcedReturnType = {};

	void PatchDialogProc_AfterInitialize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		using se::cs::winui::AddStyles;
		using se::cs::winui::RemoveStyles;
		using se::cs::winui::SetWindowIdByValue;

		restoreLeveledCreatureColumnWidths(hWnd);

		// Give IDs to controls that don't normally have one.
		SetWindowIdByValue(hWnd, "ID", CONTROL_ID_ID_STATIC);
		SetWindowIdByValue(hWnd, "Chance None", CONTROL_ID_CHANCE_NONE_STATIC);

		RemoveStyles(hWnd, DS_MODALFRAME | DS_CENTER);
		AddStyles(hWnd, WS_SIZEBOX);

		// Change the selected texture static to be a single line
		SetDlgItemText(hWnd, CONTROL_ID_ID_STATIC, "ID:");
		SetDlgItemText(hWnd, CONTROL_ID_CHANCE_NONE_STATIC, "Chance None:");

		// Change element style
		auto hStaticTextChanceNone = GetDlgItem(hWnd, CONTROL_ID_CHANCE_NONE_STATIC);
		auto hCheckBoxCalculateLevels = GetDlgItem(hWnd, CONTROL_ID_CALCULATE_LEVELS_CHECKBOX);

		{
			 // Get the current style of the element
	   		 auto styleChanceNone = GetWindowLongPtr(hStaticTextChanceNone, GWL_STYLE);
			 auto styleCheckBoxCalculateLevels = GetWindowLongPtr(hCheckBoxCalculateLevels, GWL_STYLE);

			 // Remove bits responsible for style and set a new style
			 styleChanceNone = (styleChanceNone & ~SS_TYPEMASK) | SS_RIGHT;
			 styleCheckBoxCalculateLevels |= BS_LEFTTEXT;
			 styleCheckBoxCalculateLevels |= BS_RIGHT;

			 // Set a new style for the element
			 SetWindowLongPtr(hStaticTextChanceNone, GWL_STYLE, styleChanceNone);
			 SetWindowLongPtr(hCheckBoxCalculateLevels, GWL_STYLE, styleCheckBoxCalculateLevels);
		}

		// Restore size and position
		const auto& settingsSize = settings.leveled_creature_window.size;
		const auto width = std::max(settingsSize.width, MIN_WIDTH);
		const auto height = std::max(settingsSize.height, MIN_HEIGHT);
		const auto x = settings.leveled_creature_window.x_position;
		const auto y = settings.leveled_creature_window.y_position;

		MoveWindow(hWnd, x, y, width, height, FALSE);
		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	// Force min/max window size if user scale it

	void PatchDialogProc_GetMinMaxInfo(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		const auto info = (LPMINMAXINFO)lParam;
		info->ptMinTrackSize.x = MIN_WIDTH;
		info->ptMinTrackSize.y = MIN_HEIGHT;

		forcedReturnType = 0;
	}

	// Saving window coords if user move it

	void PatchDialogProc_AfterMove(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		int short xPos = LOWORD(lParam);
		int short yPos = HIWORD(lParam);

		settings.leveled_creature_window.x_position = xPos - 8;
		settings.leveled_creature_window.y_position = yPos - 31;
	}

	namespace ResizeConstants {
		// Font 08 - Vanilla
		//constexpr auto STATIC_HEIGHT = 13;
		// Font 10
		constexpr auto STATIC_HEIGHT = 16;
		// Font 12

		constexpr auto COMBO_HEIGHT = STATIC_HEIGHT + 8;
		constexpr auto BASIC_PADDING = 2;
		constexpr auto BIG_PADDING = 6;
		constexpr auto WINDOW_EDGE_PADDING = 10;
		constexpr auto STATIC_COMBO_OFFSET = (COMBO_HEIGHT - STATIC_HEIGHT) / 2;

		constexpr auto BUTTON_WIDTH = 90;
		constexpr auto EDIT_FIELD_WIDTH = 220;
		constexpr auto EDIT_SMALL_FIELD_WIDTH = EDIT_FIELD_WIDTH / 5;
		constexpr auto STATIC_ID_WIDTH = EDIT_FIELD_WIDTH / 10;

		constexpr auto CALCULATE_LEVELS_CHECKBOX_WIDTH = 240;
		constexpr auto BLOCKED_CHECKBOX_WIDTH = 70;

		constexpr auto CONTROLS_SECTION_WIDTH = BIG_PADDING * 2 + BASIC_PADDING + STATIC_ID_WIDTH + EDIT_FIELD_WIDTH;
		constexpr auto BOTTOM_SECTION_HEIGHT = COMBO_HEIGHT + STATIC_HEIGHT + WINDOW_EDGE_PADDING * 2;

	}

	void PatchDialogProc_BeforeSize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		using namespace ResizeConstants;

		const auto clientWidth = LOWORD(lParam);
		const auto clientHeight = HIWORD(lParam);

		// Controls section

		{
			auto currentX = BIG_PADDING;
			auto currentY = WINDOW_EDGE_PADDING;

			auto idStatic = GetDlgItem(hWnd, CONTROL_ID_ID_STATIC);
			MoveWindow(idStatic, currentX, currentY + STATIC_COMBO_OFFSET, STATIC_ID_WIDTH, STATIC_HEIGHT, FALSE);

			currentX += STATIC_ID_WIDTH + BASIC_PADDING;

			auto idEdit = GetDlgItem(hWnd, CONTROL_ID_ID_EDIT);
			MoveWindow(idEdit, currentX, currentY, EDIT_FIELD_WIDTH, COMBO_HEIGHT, FALSE);
		
			currentY += COMBO_HEIGHT + BIG_PADDING;
			currentX = CONTROLS_SECTION_WIDTH - CALCULATE_LEVELS_CHECKBOX_WIDTH - BIG_PADDING;

			auto calculateLevelsCheckbox = GetDlgItem(hWnd, CONTROL_ID_CALCULATE_LEVELS_CHECKBOX);
			MoveWindow(calculateLevelsCheckbox, currentX, currentY, CALCULATE_LEVELS_CHECKBOX_WIDTH, COMBO_HEIGHT, FALSE);

			currentY += COMBO_HEIGHT + BIG_PADDING;
			currentX = CONTROLS_SECTION_WIDTH - BUTTON_WIDTH - EDIT_SMALL_FIELD_WIDTH - BIG_PADDING - BASIC_PADDING;

			auto chanceNoneStatic = GetDlgItem(hWnd, CONTROL_ID_CHANCE_NONE_STATIC);
			MoveWindow(chanceNoneStatic, currentX, currentY + STATIC_COMBO_OFFSET, BUTTON_WIDTH, STATIC_HEIGHT, FALSE);

			currentX += BUTTON_WIDTH + BASIC_PADDING;

			auto chanceNoneEdit = GetDlgItem(hWnd, CONTROL_ID_CHANCE_NONE_EDIT);
			MoveWindow(chanceNoneEdit, currentX, currentY, EDIT_SMALL_FIELD_WIDTH, COMBO_HEIGHT, FALSE);

		}

		// Leveled List Section

		{
			auto currentX = CONTROLS_SECTION_WIDTH;
			auto currentY = WINDOW_EDGE_PADDING;

			auto LEVELED_LIST_SECTION_HEIGHT = clientHeight - WINDOW_EDGE_PADDING * 2;
			auto TEXTURE_LIST_WIDTH = clientWidth - CONTROLS_SECTION_WIDTH - BIG_PADDING;

			auto leveledList = GetDlgItem(hWnd, CONTROL_ID_LEVELED_LIST);
			MoveWindow(leveledList, currentX, currentY, TEXTURE_LIST_WIDTH, LEVELED_LIST_SECTION_HEIGHT, FALSE);
		}

		// Bottom section

		{
			auto currentX = ( CONTROLS_SECTION_WIDTH - BUTTON_WIDTH * 2 - WINDOW_EDGE_PADDING ) / 2;
			auto currentY = clientHeight - BOTTOM_SECTION_HEIGHT;

			auto okButton = GetDlgItem(hWnd, CONTROL_ID_OK_BUTTON);
			MoveWindow(okButton, currentX, currentY, BUTTON_WIDTH, COMBO_HEIGHT, FALSE);

			currentX += BUTTON_WIDTH + WINDOW_EDGE_PADDING;

			auto cancelButton = GetDlgItem(hWnd, CONTROL_ID_CANCEL_BUTTON);
			MoveWindow(cancelButton, currentX, currentY, BUTTON_WIDTH, COMBO_HEIGHT, FALSE);

			currentY += COMBO_HEIGHT + WINDOW_EDGE_PADDING;
			currentX = ( CONTROLS_SECTION_WIDTH - BLOCKED_CHECKBOX_WIDTH ) / 2;

			auto blockedCheckbox = GetDlgItem(hWnd, CONTROL_ID_BLOCKED_CHECKBOX);
			MoveWindow(blockedCheckbox, currentX, currentY, BLOCKED_CHECKBOX_WIDTH, STATIC_HEIGHT, FALSE);
		}

		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_ERASENOW | RDW_INVALIDATE | RDW_ALLCHILDREN);

		// Store window size for later restoration.
		SIZE winSize = {};
		if (winui::GetWindowSize(hWnd, winSize)) {
			settings.leveled_creature_window.size = winSize;
		}

		forcedReturnType = TRUE;
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		PatchDialogProc_OverrideResult.reset();

		switch (msg) {
		case WM_SIZE:
			PatchDialogProc_BeforeSize(hWnd, msg, wParam, lParam);
			break;
		case WM_DESTROY:
			PatchDialogProc_BeforeDestroy(hWnd, msg, wParam, lParam);
		}

		if (PatchDialogProc_OverrideResult) {
			return PatchDialogProc_OverrideResult.value();
		}

		// Call original function.
		const auto CS_RenderWindowDialogProc = reinterpret_cast<WNDPROC>(0x51D5E0);
		auto vanillaResult = CS_RenderWindowDialogProc(hWnd, msg, wParam, lParam);

		switch (msg) {
		case WM_INITDIALOG:
			PatchDialogProc_AfterInitialize(hWnd, msg, wParam, lParam);
			break;
		case WM_GETMINMAXINFO:
			PatchDialogProc_GetMinMaxInfo(hWnd, msg, wParam, lParam);
			break;
		case WM_MOVE:
			PatchDialogProc_AfterMove(hWnd, msg, wParam, lParam);
			break;
		}

		return PatchDialogProc_OverrideResult.value_or(vanillaResult);
	}

	//
	//
	//

	void installPatches() {
		using memory::genJumpEnforced;

		// Patch: Extend handling.
		genJumpEnforced(0x402C3E, 0x51D5E0, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}
