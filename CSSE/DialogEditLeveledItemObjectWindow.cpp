#include "DialogEditLeveledItemObjectWindow.h"

#include "Settings.h"

#include "LogUtil.h"

#include "MemoryUtil.h"

namespace se::cs::dialog::edit_leveled_item_object_window {

	//
	// Configuration
	//

	constexpr auto ENABLE_ALL_OPTIMIZATIONS = true;
	constexpr auto LOG_PERFORMANCE_RESULTS = false;

	//
	// Extended window messages
	//

	std::optional<LRESULT> messageResult;

	std::chrono::high_resolution_clock::time_point initializationTimer;

	void PatchDialogProc_BeforeInitialize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if constexpr (LOG_PERFORMANCE_RESULTS) {
			initializationTimer = std::chrono::high_resolution_clock::now();
		}

	}

	static std::optional<LRESULT> PatchDialogProc_OverrideResult = {};

	void PatchDialogProc_AfterInitialize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if constexpr (LOG_PERFORMANCE_RESULTS) {
			auto timeToInitialize = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - initializationTimer);
			log::stream << "Displaying leveled item object data took " << timeToInitialize.count() << "ms" << std::endl;
		}

		// Get the current window size
		RECT rect;
		GetWindowRect(hWnd, &rect);

		const auto width = rect.right - rect.left;
		const auto height = rect.bottom - rect.top;

		// Restore window size and position.
		const auto x = settings.leveled_item_window.x_position;
		const auto y = settings.leveled_item_window.y_position;

		MoveWindow(hWnd, x, y, width, height, FALSE);
		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	// Saving window coords if user move it.
	void PatchDialogProc_AfterMove(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		int short xPos = LOWORD(lParam);
		int short yPos = HIWORD(lParam);

		settings.leveled_item_window.x_position = xPos - 3;
		settings.leveled_item_window.y_position = yPos - 26;
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		PatchDialogProc_OverrideResult.reset();
		messageResult = {};

		switch (msg) {
		case WM_INITDIALOG:
			PatchDialogProc_BeforeInitialize(hWnd, msg, wParam, lParam);
			break;
		}

		if (messageResult) {
			return messageResult.value();
		}

		if (PatchDialogProc_OverrideResult) {
			return PatchDialogProc_OverrideResult.value();
		}

		// Call original function.
		const auto CS_LeveledItemDialogProc = reinterpret_cast<WNDPROC>(0x520240);
		auto vanillaResult = CS_LeveledItemDialogProc(hWnd, msg, wParam, lParam);

		switch (msg) {
		case WM_INITDIALOG:
			PatchDialogProc_AfterInitialize(hWnd, msg, wParam, lParam);
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
		genJumpEnforced(0x401D66, 0x520240, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}
