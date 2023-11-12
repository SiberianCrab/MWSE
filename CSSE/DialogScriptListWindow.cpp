#include "DialogScriptListWindow.h"

#include "CSDataHandler.h"
#include "CSRecordHandler.h"
#include "CSScript.h"
#include "EditBasicExtended.h"
#include "Settings.h"

#include "LogUtil.h"
#include "MemoryUtil.h"
#include "StringUtil.h"
#include "WinUIUtil.h"

namespace se::cs::dialog::script_list_window {

	static std::string currentSearchText;
	static std::optional<std::regex> currentSearchRegex;
	static bool modeShowModifiedOnly = false;

	bool matchDispatcher(const std::string_view& haystack) {
		if (currentSearchRegex) {
			return std::regex_search(haystack.data(), currentSearchRegex.value());
		}
		else if (settings.object_window.case_sensitive) {
			return string::contains(haystack, currentSearchText);
		}
		else {
			return string::cicontains(haystack, currentSearchText);
		}
	}

	bool FilterScriptList_ScriptMatchesSearch(const Script* script) {
		if (modeShowModifiedOnly && !script->getModified()) {
			return false;
		}
		if (currentSearchText.empty()) {
			return true;
		}

		return matchDispatcher(script->getObjectID());
	}

	void RefreshScriptListBox(HWND hWnd) {
		auto scriptsListBox = GetDlgItem(hWnd, CONTROL_ID_SCRIPT_LIST);
		auto scripts = DataHandler::get()->recordHandler->scripts;
		char buffer[256];

		SendMessageA(scriptsListBox, WM_SETREDRAW, FALSE, NULL);

		SendMessageA(scriptsListBox, LB_RESETCONTENT, 0, 0);
		for (const auto s : *scripts) {
			if (!FilterScriptList_ScriptMatchesSearch(s)) {
				continue;
			}

			const char* suffix = "";
			if (s->flags & 0x20) {
				suffix = "      DELETED";
			}
			else if (s->flags & 2) {
				suffix = " *";
			}
			snprintf(buffer, sizeof(buffer), "%s%s", s->getObjectID(), suffix);

			auto i = SendMessageA(scriptsListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
			SendMessageA(scriptsListBox, LB_SETITEMDATA, i, (LPARAM)s);
		}

		SendMessageA(scriptsListBox, WM_SETREDRAW, TRUE, NULL);
		RedrawWindow(scriptsListBox, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	void OnFilterEditChanged(HWND hWnd) {
		using namespace se::cs::winui;

		// Get current search text.
		auto searchEdit = GetDlgItem(hWnd, CONTROL_ID_FILTER_EDIT);
		auto newText = GetWindowTextA(searchEdit);

		// Transform the search text to lowercase and clear stray characters.
		string::to_lower(newText);

		if (!string::equal(currentSearchText, newText)) {
			currentSearchText = std::move(newText);

			// Regex crunching can be slow, so only do it once.
			if (settings.object_window.use_regex) {
				auto flags = std::regex_constants::extended | std::regex_constants::optimize | std::regex_constants::nosubs;
				if (!settings.object_window.case_sensitive) {
					flags |= std::regex_constants::icase;
				}

				try {
					currentSearchRegex = std::regex(currentSearchText, flags);
				}
				catch (const std::regex_error& e) {
					log::stream << "Regex error when searching script list window: " << e.what() << std::endl;
					currentSearchRegex = {};

					// TODO: Paint the background of the search input red or something.
				}
			}
			else {
				currentSearchRegex = {};
			}

			// Search affects cell list.
			RefreshScriptListBox(hWnd);
		}
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

		constexpr auto BUTTON_WIDTH = 130;
		constexpr auto CLEAR_BUTTON_WIDTH = 20;
		constexpr auto STATIC_WIDTH = 50;
		constexpr auto SEARCH_WIDTH = 140;

		constexpr auto BOTTOM_SECTION = COMBO_HEIGHT + BIG_PADDING * 2 + WINDOW_EDGE_PADDING;

	}

	void CALLBACK PatchDialogProc_BeforeSize(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
		using winui::GetRectHeight;
		using winui::GetRectWidth;
		using winui::GetWindowRelativeRect;

		using namespace ResizeConstants;

		auto scriptListView = GetDlgItem(hDlg, CONTROL_ID_SCRIPT_LIST);
		auto showModifiedButton = GetDlgItem(hDlg, CONTROL_ID_SHOW_MODIFIED_ONLY_BUTTON);
		auto clearSearchFiedButton = GetDlgItem(hDlg, CONTROL_ID_CLEAR_BUTTON);
		auto searchLabel = GetDlgItem(hDlg, CONTROL_ID_FILTER_LABEL);
		auto searchEdit = GetDlgItem(hDlg, CONTROL_ID_FILTER_EDIT);

		const auto mainWidth = LOWORD(lParam);
		const auto mainHeight = HIWORD(lParam);

		// Update list view area.
		RECT listViewRect = {};
		GetWindowRelativeRect(scriptListView, &listViewRect);
		// Border padding.
		MoveWindow(scriptListView, WINDOW_EDGE_PADDING, WINDOW_EDGE_PADDING, mainWidth - WINDOW_EDGE_PADDING * 2, mainHeight - BOTTOM_SECTION, FALSE);

		// Update the search bar placement.
		int currentY = mainHeight - COMBO_HEIGHT - BIG_PADDING;
		int currentX = WINDOW_EDGE_PADDING;

		MoveWindow(showModifiedButton, currentX, currentY, BUTTON_WIDTH, COMBO_HEIGHT, TRUE);
		MoveWindow(clearSearchFiedButton, mainWidth - WINDOW_EDGE_PADDING - CLEAR_BUTTON_WIDTH, currentY, CLEAR_BUTTON_WIDTH, COMBO_HEIGHT, TRUE);
		MoveWindow(searchLabel, mainWidth - WINDOW_EDGE_PADDING - CLEAR_BUTTON_WIDTH - SEARCH_WIDTH - BASIC_PADDING - STATIC_WIDTH, currentY + STATIC_COMBO_OFFSET, STATIC_WIDTH, STATIC_HEIGHT, TRUE);
		MoveWindow(searchEdit, mainWidth - WINDOW_EDGE_PADDING - CLEAR_BUTTON_WIDTH - SEARCH_WIDTH, currentY, SEARCH_WIDTH, COMBO_HEIGHT, FALSE);

		RedrawWindow(hDlg, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	void CALLBACK PatchDialogProc_AfterCreate(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		auto hInstance = (HINSTANCE)GetWindowLongA(hWnd, GWLP_HINSTANCE);

		// Ensure our custom filter box is added.
		auto hDlgShowModifiedOnly = CreateWindowExA(NULL, WC_BUTTON, "Show modified only", BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_CHILD | WS_VISIBLE | WS_GROUP, 0, 0, 0, 0, hWnd, (HMENU)CONTROL_ID_SHOW_MODIFIED_ONLY_BUTTON, hInstance, NULL);
		auto hDlgFilterStatic = CreateWindowExA(NULL, WC_STATIC, "Filter:", SS_RIGHT | WS_CHILD | WS_VISIBLE | WS_GROUP, 0, 0, 0, 0, hWnd, (HMENU)CONTROL_ID_FILTER_LABEL, hInstance, NULL);
		auto hDlgFilterEdit = CreateWindowExA(WS_EX_CLIENTEDGE, WC_EDIT, "", ES_LEFT | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 0, 0, 0, 0, hWnd, (HMENU)CONTROL_ID_FILTER_EDIT, hInstance, NULL);
		auto hClearButton = CreateWindowExA(NULL, WC_BUTTON, "X", WS_CHILD | WS_VISIBLE | WS_GROUP, 0, 0, 0, 0, hWnd, (HMENU)CONTROL_ID_CLEAR_BUTTON, hInstance, NULL);
		if (hDlgFilterEdit) {
			SetWindowSubclass(hDlgFilterEdit, ui_subclass::edit::BasicExtendedProc, NULL, NULL);

			auto font = SendMessageA(hWnd, WM_GETFONT, FALSE, FALSE);
			SendMessageA(hDlgShowModifiedOnly, WM_SETFONT, font, MAKELPARAM(TRUE, FALSE));
			SendMessageA(hDlgFilterStatic, WM_SETFONT, font, MAKELPARAM(TRUE, FALSE));
			SendMessageA(hDlgFilterEdit, WM_SETFONT, font, MAKELPARAM(TRUE, FALSE));
			SendMessageA(hClearButton, WM_SETFONT, font, MAKELPARAM(TRUE, FALSE));
		}
		else {
			log::stream << "ERROR: Could not create search control!" << std::endl;
		}

		// Make window larger.
		SetWindowPos(hWnd, NULL, 0, 0, 380, 500, SWP_NOMOVE);

		// Initialize controls with last filter settings, and refresh script list.
		if (!currentSearchText.empty()) {
			SetWindowTextA(hDlgFilterEdit, currentSearchText.c_str());
		}
		SendMessageA(hDlgShowModifiedOnly, BM_SETCHECK, modeShowModifiedOnly ? BST_CHECKED : BST_UNCHECKED, 0);
		RefreshScriptListBox(hWnd);
	}

	// Set min/max window size for scaling.
	constexpr auto MIN_WIDTH = 380u;
	constexpr auto MIN_HEIGHT = 500u;

	// Force min/max window size for scaling.
	void PatchDialogProc_GetMinMaxInfo(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		const auto info = (LPMINMAXINFO)lParam;
		info->ptMinTrackSize.x = MIN_WIDTH;
		info->ptMinTrackSize.y = MIN_HEIGHT;

	}

	void CALLBACK PatchDialogProc_BeforeCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		const auto command = HIWORD(wParam);
		const auto id = LOWORD(wParam);

		switch (command) {
		case BN_CLICKED:
			switch (id) {
			case CONTROL_ID_SHOW_MODIFIED_ONLY_BUTTON:
				modeShowModifiedOnly = SendDlgItemMessageA(hWnd, id, BM_GETCHECK, 0, 0);
				RefreshScriptListBox(hWnd);
				break;
			case CONTROL_ID_CLEAR_BUTTON:
				// Handle clear button click
				SetWindowTextA(GetDlgItem(hWnd, CONTROL_ID_FILTER_EDIT), "");
				currentSearchText = ""; // Update the stored search text
				RefreshScriptListBox(hWnd);
				break;
			}
			break;
		case EN_CHANGE:
			switch (id) {
			case CONTROL_ID_FILTER_EDIT:
				OnFilterEditChanged(hWnd);
				break;
			}
			break;
		}
	}

	LRESULT CALLBACK PatchDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		// Handle pre-patches.
		switch (msg) {
		case WM_COMMAND:
			PatchDialogProc_BeforeCommand(hWnd, msg, wParam, lParam);
			break;
		case WM_SIZE:
			PatchDialogProc_BeforeSize(hWnd, msg, wParam, lParam);
			return FALSE;
		}

		// Call original function.
		const auto CS_ScriptListDialogProc = reinterpret_cast<WNDPROC>(0x42DBD0);
		auto result = CS_ScriptListDialogProc(hWnd, msg, wParam, lParam);

		// Handle post-patches.
		switch (msg) {
		case WM_INITDIALOG:
			PatchDialogProc_AfterCreate(hWnd, msg, wParam, lParam);
			break;
		case WM_GETMINMAXINFO:
			PatchDialogProc_GetMinMaxInfo(hWnd, msg, wParam, lParam);
			break;
		}

		return result;
	}

	void installPatches() {
		using memory::genJumpEnforced;

		// Patch: Extend window messages.
		genJumpEnforced(0x403184, 0x42DBD0, reinterpret_cast<DWORD>(PatchDialogProc));
	}
}
