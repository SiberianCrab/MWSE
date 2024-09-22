#include "DialogEditClassWindow.h"

#include "Settings.h"

#include "LogUtil.h"

#include "MemoryUtil.h"

#include "CSClass.h"

#include "DialogProcContext.h"

namespace se::cs::dialog::edit_class_window {

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
		SendDlgItemMessageA(hWnd, CONTROL_ID_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_PRIMARY_ATTRIBUTES_1_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_PRIMARY_ATTRIBUTES_2_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_SPECIALIZATION_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MAJOR_SKILLS_1_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MAJOR_SKILLS_2_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MAJOR_SKILLS_3_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MAJOR_SKILLS_4_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MAJOR_SKILLS_5_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MINOR_SKILLS_1_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MINOR_SKILLS_2_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MINOR_SKILLS_3_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MINOR_SKILLS_4_COMBO, WM_SETREDRAW, wParam, NULL);
		SendDlgItemMessageA(hWnd, CONTROL_ID_MINOR_SKILLS_5_COMBO, WM_SETREDRAW, wParam, NULL);
	}

	void PatchDialogProc_BeforeInitialize(DialogProcContext& context) {
		if constexpr (LOG_PERFORMANCE_RESULTS) {
			initializationTimer = std::chrono::high_resolution_clock::now();
		}

	}

	void PatchDialogProc_AfterInitialize(DialogProcContext& context) {

		if constexpr (LOG_PERFORMANCE_RESULTS) {
			auto timeToInitialize = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - initializationTimer);
			log::stream << "Displaying class data took " << timeToInitialize.count() << "ms" << std::endl;
		}

		// Get the current window size
		RECT rect;
		GetWindowRect(context.getWindowHandle(), &rect);

		const auto width = rect.right - rect.left;
		const auto height = rect.bottom - rect.top;

		// Restore window size and position.
		const auto x = settings.class_window.x_position;
		const auto y = settings.class_window.y_position;

		MoveWindow(context.getWindowHandle(), x, y, width, height, FALSE);
		RedrawWindow(context.getWindowHandle(), NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	// Saving window coords if user move it.
	void PatchDialogProc_AfterMove(DialogProcContext& context) {
		settings.class_window.x_position = context.getMovedX() - 3;
		settings.class_window.y_position = context.getMovedY() - 26;
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DialogProcContext context(hWnd, msg, wParam, lParam, 0x42AAB0);

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
		genJumpEnforced(0x402036, 0x42AAB0, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}