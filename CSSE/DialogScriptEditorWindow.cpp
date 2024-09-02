#include "DialogScriptEditorWindow.h"

#include <Richedit.h>

#include "MemoryUtil.h"
#include "WinUIUtil.h"

#include "Settings.h"
#include "RR_Settings.h"

namespace se::cs::dialog::script_editor_window {

	void __stdcall PatchRichEditSetFormat(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		// Call original code.
		SendMessageA(hWnd, msg, wParam, lParam);

		// Set font face and size. Remove bold effect.
		CHARFORMATA format;
		format.cbSize = sizeof(CHARFORMATA);
		format.dwMask = CFM_EFFECTS | CFM_FACE | CFM_SIZE;
		format.dwEffects = 0;
		format.yHeight = DialogScriptEditorWindow_FONT_SIZE * settings.script_editor.font_size;

		SendMessageA(hWnd, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&format);
	}

	void installPatches() {
		using memory::genCallUnprotected;

		genCallUnprotected(0x42D5D9, reinterpret_cast<DWORD>(PatchRichEditSetFormat), 6);
	}
}
