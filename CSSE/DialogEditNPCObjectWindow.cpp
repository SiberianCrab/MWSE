#include "DialogEditNPCObjectWindow.h"

#include "Settings.h"

#include "LogUtil.h"

#include "MemoryUtil.h"

#include "DialogProcContext.h"

namespace se::cs::dialog::edit_npc_object_window {

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
		SendDlgItemMessageA(hWnd, CONTROL_ID_BLOOD_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_CLASS_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_DETAILS_LIST, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_FACTION_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_FACTION_RANK_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_HAIR_LIST, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_HEAD_LIST, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_RACE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SCRIPT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SCRIPT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SKILLS_LIST, WM_SETREDRAW, wParam, NULL);
	}

	void PatchDialogProc_BeforeInitialize(DialogProcContext& context) {
		if constexpr (LOG_PERFORMANCE_RESULTS) {
			initializationTimer = std::chrono::high_resolution_clock::now();
		}

		// Optimize redraws.
		setRedrawOnExpensiveWindows(context.getWindowHandle(), false);
	}

	void PatchDialogProc_AfterInitialize(DialogProcContext& context) {
		// Restore redraws.
		setRedrawOnExpensiveWindows(context.getWindowHandle(), true);

		if constexpr (LOG_PERFORMANCE_RESULTS) {
			auto timeToInitialize = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - initializationTimer);
			log::stream << "Displaying NPC object data took " << timeToInitialize.count() << "ms" << std::endl;
		}

		// Get the current window size
		RECT rect;
		GetWindowRect(hWnd, &rect);

		const auto width = rect.right - rect.left;
		const auto height = rect.bottom - rect.top;

		// Restore window size and position.
		const auto x = settings.NPC_object_window.x_position;
		const auto y = settings.NPC_object_window.y_position;

		MoveWindow(hWnd, x, y, width, height, FALSE);
		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	// Saving window coords if user move it.
	void PatchDialogProc_AfterMove(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		int short xPos = LOWORD(lParam);
		int short yPos = HIWORD(lParam);

		settings.NPC_object_window.x_position = xPos - 3;
		settings.NPC_object_window.y_position = yPos - 26;
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DialogProcContext context(hWnd, msg, wParam, lParam, 0x423060);

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
			PatchDialogProc_AfterMove(hWnd, msg, wParam, lParam);
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
		genJumpEnforced(0x40313E, 0x423060, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}
