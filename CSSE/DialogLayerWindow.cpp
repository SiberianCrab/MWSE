#include "DialogLayersWindow.h"
#include "WindowMain.h"

#include <commctrl.h>
#include <string>

#define IDC_LAYERS_LIST 2001
#define IDC_ADD_LAYER_BTN 2002
#define MAX_LAYERS 32

namespace se::cs::dialog::layer_window {

	HWND hLayersWnd = NULL;
	bool isLayerWndForceHidden = false;

	std::vector<LayerData> g_Layers;
	static COLORREF g_CustomColors[16] = { 0 }; // color picker history

	// NI::Color uses rbg order, while COLORREF uses rgb order.
	COLORREF NIColorToRef(const NI::Color& c) {
		return RGB(
			(int)(c.r * 255.0f),
			(int)(c.b * 255.0f),
			(int)(c.g * 255.0f)
		);
	}

	NI::Color RefToNIColor(COLORREF c) {
		return NI::Color{
			GetRValue(c) / 255.0f,
			GetBValue(c) / 255.0f,
			GetGValue(c) / 255.0f
		};
	}

	// Hacky way to check if the render window is visible by reading the View menu's Render Window item.
	// We can use IsIconic(hRender), but animations window hides the render window without triggering that, so this is more reliable.
	bool IsRenderWindowVisible(HMENU viewMenu) {
		if (viewMenu) {
			const int rendererPos = 2;
			const UINT state = GetMenuState(viewMenu, rendererPos, MF_BYPOSITION);
			if (state != 0xFFFFFFFF && (state & MF_CHECKED)) {
				return TRUE;
			}
		}
		return FALSE;
	}


	std::vector<LayerData>& GetLayers() {
		return g_Layers;
	}

	LRESULT CALLBACK LayersWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		static HWND hListView;
		static HWND hBtnAdd;

		switch (msg) {
		case WM_CREATE: {

			hListView = CreateWindowExA(0, WC_LISTVIEW, "",
				WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_EDITLABELS,
				0, 0, 0, 0,
				hWnd, (HMENU)IDC_LAYERS_LIST, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

			ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

			LVCOLUMNA lvc = { 0 };
			lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;

			lvc.fmt = LVCFMT_LEFT;
			lvc.cx = 110;
			lvc.pszText = (LPSTR)"Name";
			ListView_InsertColumn(hListView, 0, &lvc);

			lvc.fmt = LVCFMT_CENTER;
			lvc.cx = 45;
			lvc.pszText = (LPSTR)"Color";
			ListView_InsertColumn(hListView, 1, &lvc);

			lvc.cx = 45;
			lvc.pszText = (LPSTR)"Vis";
			ListView_InsertColumn(hListView, 2, &lvc);

			lvc.cx = 50;
			lvc.pszText = (LPSTR)"Ovrl";
			ListView_InsertColumn(hListView, 3, &lvc);

			hBtnAdd = CreateWindowExA(0, "BUTTON", "+",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
				0, 0, 0, 0,
				hWnd, (HMENU)IDC_ADD_LAYER_BTN, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

			HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hListView, WM_SETFONT, (WPARAM)hFont, 0);
			SendMessage(hBtnAdd, WM_SETFONT, (WPARAM)hFont, 0);
			break;
		}

		case WM_SIZE: {
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			int btnHeight = 30;

			MoveWindow(hListView, 0, 0, width, height - btnHeight, TRUE);

			MoveWindow(hBtnAdd, 0, height - btnHeight, width, btnHeight, TRUE);
			break;
		}

		case WM_DRAWITEM: {
			LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
			if (pDIS->CtlID == IDC_LAYERS_LIST) {
				if (pDIS->itemID >= (int)g_Layers.size()) break;

				LayerData& layer = g_Layers[pDIS->itemID];

				if (pDIS->itemState & ODS_SELECTED) {
					FillRect(pDIS->hDC, &pDIS->rcItem, GetSysColorBrush(COLOR_HIGHLIGHT));
					SetTextColor(pDIS->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
				}
				else {
					FillRect(pDIS->hDC, &pDIS->rcItem, GetSysColorBrush(COLOR_WINDOW));
					SetTextColor(pDIS->hDC, GetSysColor(COLOR_WINDOWTEXT));
				}
				SetBkMode(pDIS->hDC, TRANSPARENT);

				RECT rcLabel, rcColor, rcVis, rcOver;
				ListView_GetSubItemRect(hListView, pDIS->itemID, 0, LVIR_BOUNDS, &rcLabel);
				ListView_GetSubItemRect(hListView, pDIS->itemID, 1, LVIR_BOUNDS, &rcColor);
				ListView_GetSubItemRect(hListView, pDIS->itemID, 2, LVIR_BOUNDS, &rcVis);
				ListView_GetSubItemRect(hListView, pDIS->itemID, 3, LVIR_BOUNDS, &rcOver);

				rcLabel.left += 4; // some padding
				DrawTextA(pDIS->hDC, layer.layerName.c_str(), -1, &rcLabel, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

				InflateRect(&rcColor, -4, -4);
				HBRUSH hBrush = CreateSolidBrush(NIColorToRef(layer.getLayerColor()));
				FillRect(pDIS->hDC, &rcColor, hBrush);
				FrameRect(pDIS->hDC, &rcColor, (HBRUSH)GetStockObject(BLACK_BRUSH)); // Border
				DeleteObject(hBrush);

				UINT stateVis = DFCS_BUTTONCHECK | (!layer.isLayerHidden ? DFCS_CHECKED : 0);
				DrawFrameControl(pDIS->hDC, &rcVis, DFC_BUTTON, stateVis);

				UINT stateOver = DFCS_BUTTONCHECK | (layer.isOverlayActive ? DFCS_CHECKED : 0);
				DrawFrameControl(pDIS->hDC, &rcOver, DFC_BUTTON, stateOver);

				return TRUE;
			}
			break;
		}

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDC_ADD_LAYER_BTN) {
				if (g_Layers.size() < MAX_LAYERS) {
					LayerData newLayer;
					newLayer.layerName = "Layer " + std::to_string(g_Layers.size() + 1);
					g_Layers.push_back(newLayer);

					LVITEMA lvI = { 0 };
					lvI.mask = LVIF_TEXT;

					lvI.iItem = (int)g_Layers.size() - 1;
					lvI.pszText = LPSTR_TEXTCALLBACK;
					ListView_InsertItem(hListView, &lvI);

					// maybe start editing the new item's name:
					// ListView_EditLabel(hListView, lvI.iItem);
				}
				else {
					MessageBoxA(hWnd, "Maximum of 32 layers reached.", "Limit Reached", MB_OK | MB_ICONINFORMATION);
				}
			}
			break;
		}

		case WM_NOTIFY: {
			LPNMHDR lpnm = (LPNMHDR)lParam;

			if (lpnm == NULL)
				break;

			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == NM_CLICK) {
				LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;

				if (lpnmitem->iItem != -1 && lpnmitem->iItem < (int)g_Layers.size()) {
					LayerData& layer = g_Layers[lpnmitem->iItem];

					//color picker
					if (lpnmitem->iSubItem == 1) {
						CHOOSECOLORA cc = { 0 };
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hWnd;
						cc.lpCustColors = g_CustomColors;
						cc.rgbResult = NIColorToRef(layer.getLayerColor());
						cc.Flags = CC_FULLOPEN | CC_RGBINIT;

						if (ChooseColorA(&cc)) {
							layer.setLayerColor(RefToNIColor(cc.rgbResult));
							InvalidateRect(hListView, NULL, FALSE);
							// TODO: Trigger scene graph update here??? Might be unnecessary since material is shared
						}
					}

					// visibility toggle
					else if (lpnmitem->iSubItem == 2) {
						layer.isLayerHidden = !layer.isLayerHidden;
						InvalidateRect(hListView, NULL, FALSE);
						// TODO: Trigger scene graph update here
					}

					// color overlay toggle
					else if (lpnmitem->iSubItem == 3) {
						layer.isOverlayActive = !layer.isOverlayActive;
						InvalidateRect(hListView, NULL, FALSE);
						// TODO: Trigger overlay render update here
					}
				}
			}

			// double-click to edit layer name
			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == NM_DBLCLK) {
				LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
				if (lpnmitem->iItem != -1 && lpnmitem->iItem < (int)g_Layers.size()) {

					if (lpnmitem->iSubItem == 0) {
						ListView_EditLabel(hListView, lpnmitem->iItem);
					}
				}
			}

			// layer name edit completed
			if (lpnm->idFrom == IDC_LAYERS_LIST && (lpnm->code == LVN_ENDLABELEDIT)) {
				LPNMLVDISPINFOA pDisp = (LPNMLVDISPINFOA)lParam;
				if (pDisp && pDisp->item.iItem >= 0 && pDisp->item.iItem < (int)g_Layers.size()) {

					if (pDisp->item.pszText) {

						g_Layers[pDisp->item.iItem].layerName = std::string(pDisp->item.pszText);

						InvalidateRect(hListView, NULL, FALSE);
					}
				}
			}

			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == LVN_KEYDOWN) {
				LPNMLVKEYDOWN pnkd = (LPNMLVKEYDOWN)lParam;

				if (pnkd->wVKey == VK_DELETE) {

					int iItem = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);

					if (iItem != -1 && iItem < (int)g_Layers.size()) {
						// TODO: Trigger scene graph update here
						// 
						g_Layers.erase(g_Layers.begin() + iItem);

						ListView_DeleteItem(hListView, iItem);
					}
				}
			}

			break;
		}

		case WM_CLOSE:
			// just in case
			ShowWindow(hWnd, SW_HIDE);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}


	void createLayersWindow() {

		if (hLayersWnd) {
			ShowWindow(hLayersWnd, SW_SHOW);
			if (IsIconic(hLayersWnd)) OpenIcon(hLayersWnd);
			SetForegroundWindow(hLayersWnd);
			return;
		}

		WNDCLASSEXA wc = {};
		wc.cbSize = sizeof(WNDCLASSEXA);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = LayersWindowProc;
		wc.hInstance = se::cs::window::main::hInstance::get();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszClassName = "CSSE_LayersWindow";
		RegisterClassExA(&wc);

		hLayersWnd = CreateWindowExA(
			WS_EX_TOOLWINDOW,
			"CSSE_LayersWindow",
			"Layers",
			WS_VISIBLE | WS_CAPTION | WS_THICKFRAME,
			100, 100, 270, 400,
			se::cs::window::main::ghWnd::get(),
			NULL,
			se::cs::window::main::hInstance::get(),
			NULL
		);
	}

	void toggleLayersWindow(bool show) {
		if (hLayersWnd) {
			ShowWindow(hLayersWnd, show ? SW_RESTORE : SW_MINIMIZE);
		}
		else {
			createLayersWindow();
		}
	}

	// If render window became minimized, minimize our layers window too.
	// BUG: won't trigger if the render window is brought back up via closing the animation window with a close button.
	void forceToggleLayersWindow(HMENU viewMenu) {
		if (hLayersWnd) {
			if (IsRenderWindowVisible(viewMenu))
			{
				if (isLayerWndForceHidden) {
					toggleLayersWindow(true);
					isLayerWndForceHidden = false;
				}
			}
			else {
				isLayerWndForceHidden = !IsIconic(hLayersWnd);
				toggleLayersWindow(false);
			}
		}
	}

	void refreshLayersMenuItem(HMENU viewMenu) {
		if (viewMenu) {

			UINT check = (hLayersWnd != NULL && !IsIconic(hLayersWnd)) ? MF_CHECKED : MF_UNCHECKED;
			CheckMenuItem(viewMenu, se::cs::window::main::MENU_ID_VIEW_LAYERS_WINDOW, check);

			UINT enable = IsRenderWindowVisible(viewMenu) ? MF_ENABLED : MF_GRAYED;
			EnableMenuItem(viewMenu, se::cs::window::main::MENU_ID_VIEW_LAYERS_WINDOW, enable);
		}
	}
}