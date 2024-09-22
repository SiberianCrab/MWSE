#include "DialogEditRaceWindow.h"

#include "Settings.h"

#include "LogUtil.h"

#include "MemoryUtil.h"

#include "CSRace.h"

#include "DialogProcContext.h"

namespace se::cs::dialog::edit_race_window {

	//
	// Configuration
	//

	constexpr auto ENABLE_ALL_OPTIMIZATIONS = true;
	constexpr auto LOG_PERFORMANCE_RESULTS = false;

	//
	// Extended window messages.
	//

	std::chrono::high_resolution_clock::time_point initializationTimer;

	void setRedrawOnExpensiveWindows(HWND hWnd, bool redraw) {
		if constexpr (!ENABLE_ALL_OPTIMIZATIONS) {
			return;
		}

		const auto wParam = redraw ? TRUE : FALSE;
		SendDlgItemMessageA(hWnd, CONTROL_ID_ID_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_1_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_2_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_3_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_4_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_5_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_6_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILL_BONUS_7_COMBO, WM_SETREDRAW, wParam, NULL);
	}

	void PatchDialogProc_BeforeInitialize(DialogProcContext& context) {
		if constexpr (LOG_PERFORMANCE_RESULTS) {
			initializationTimer = std::chrono::high_resolution_clock::now();
		}

	}

	void PatchDialogProc_AfterInitialize(DialogProcContext& context) {

		if constexpr (LOG_PERFORMANCE_RESULTS) {
			auto timeToInitialize = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - initializationTimer);
			log::stream << "Displaying race data took " << timeToInitialize.count() << "ms" << std::endl;
		}

		// Get the current window size
		RECT rect;
		GetWindowRect(context.getWindowHandle(), &rect);

		const auto width = rect.right - rect.left;
		const auto height = rect.bottom - rect.top;

		// Restore window size and position.
		const auto x = settings.race_window.x_position;
		const auto y = settings.race_window.y_position;

		MoveWindow(context.getWindowHandle(), x, y, width, height, FALSE);
		RedrawWindow(context.getWindowHandle(), NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	// Saving window coords if user move it.
	void PatchDialogProc_AfterMove(DialogProcContext& context) {
		settings.race_window.x_position = context.getMovedX() - 3;
		settings.race_window.y_position = context.getMovedY() - 26;
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DialogProcContext context(hWnd, msg, wParam, lParam, 0x429670);

		switch (msg) {
		case WM_INITDIALOG:
			PatchDialogProc_BeforeInitialize(context);
			break;
		}

		// Call original function, or return early if we already have a result.
		if (context.hasResult()) {
			return context.getResult();
		}
		else {
			context.callOriginalFunction();
		}

		switch (msg) {
		case WM_INITDIALOG:
			PatchDialogProc_AfterInitialize(context);
			break;
		case WM_MOVE:
			PatchDialogProc_AfterMove(context);
			break;
		}

		return context.getResult();
	}

	//
	//
	//

	void installPatches() {
		using memory::genJumpEnforced;

		// Patch: Extend handling.
		genJumpEnforced(0x403BFC, 0x429670, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}