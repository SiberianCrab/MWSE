#include "DialogEditSpellObjectWindow.h"

#include "Settings.h"

#include "LogUtil.h"

#include "MemoryUtil.h"

#include "DialogProcContext.h"

namespace se::cs::dialog::edit_spell_object_window {

	//
	// Configuration
	//

	constexpr auto ENABLE_ALL_OPTIMIZATIONS = true;
	constexpr auto LOG_PERFORMANCE_RESULTS = false;

	//
	// Extended window messages.
	//

	std::chrono::high_resolution_clock::time_point initializationTimer;

	void setRedrawOnExpensiveWindows(DialogProcContext& context, bool redraw) {
		if constexpr (!ENABLE_ALL_OPTIMIZATIONS) {
			return;
		}
		
		const auto hWnd = context.getWindowHandle();
		const auto wParam = redraw ? TRUE : FALSE;
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT1_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT1_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT1_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT2_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT2_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT2_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT3_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT3_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT3_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT4_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT4_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT4_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT5_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT5_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT5_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT6_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT6_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT6_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT7_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT7_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT7_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT8_EFFECT_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT8_EFFECT_VAR_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_EFFECT8_RANGE_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_TYPE_COMBO, WM_SETREDRAW, wParam, NULL);
	}

	void PatchDialogProc_BeforeInitialize(DialogProcContext& context) {
		if constexpr (LOG_PERFORMANCE_RESULTS) {
			initializationTimer = std::chrono::high_resolution_clock::now();
		}

		// Optimize redraws.
		setRedrawOnExpensiveWindows(context, false);
	}

	void PatchDialogProc_AfterInitialize(DialogProcContext& context) {
		// Restore redraws.
		setRedrawOnExpensiveWindows(context, true);

		if constexpr (LOG_PERFORMANCE_RESULTS) {
			auto timeToInitialize = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - initializationTimer);
			log::stream << "Displaying spell object data took " << timeToInitialize.count() << "ms" << std::endl;
		}

		// Get the current window size
		RECT rect;
		GetWindowRect(context.getWindowHandle(), &rect);

		const auto width = rect.right - rect.left;
		const auto height = rect.bottom - rect.top;

		// Restore window size and position.
		const auto x = settings.spell_object_window.x_position;
		const auto y = settings.spell_object_window.y_position;

		MoveWindow(context.getWindowHandle(), x, y, width, height, FALSE);
		RedrawWindow(context.getWindowHandle(), NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	// Saving window coords if user move it.
	void PatchDialogProc_AfterMove(DialogProcContext& context) {
		settings.spell_object_window.x_position = context.getMovedX() - 3;
		settings.spell_object_window.y_position = context.getMovedY() - 26;
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DialogProcContext context(hWnd, msg, wParam, lParam, 0x432AE0);

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
		genJumpEnforced(0x401299, 0x432AE0, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}
