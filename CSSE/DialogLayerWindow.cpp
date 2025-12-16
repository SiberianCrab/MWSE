#include "DialogLayersWindow.h"
#include "DialogRenderWindow.h"
#include "RenderWindowSelectionData.h"
#include "WindowMain.h"

#include <commctrl.h>

#define IDC_LAYERS_LIST 2001
#define IDC_ADD_LAYER_BTN 2002
#define IDM_LAYER_MOVE 3001
#define IDM_LAYER_CLEAR 3002
#define MAX_LAYERS 32

namespace se::cs::dialog::layer_window {

	HWND hLayersWnd = NULL;
	bool isLayerWndForceHidden = false;

	std::vector<LayerData*> g_Layers;
	std::unordered_map<size_t, LayerData*> g_LayersIdMap;
	std::unordered_map<Reference*, LayerData*> g_ObjectLayerMap;

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

	void LayerData::removeObject(Reference* objRef) {
		if (!objRef) return;

		updateObject(objRef, true);

		if (perCellReferences.find(objRef) != perCellReferences.end()) {
			perCellReferences.erase(objRef);
			g_ObjectLayerMap.erase(objRef);
		}
	}

	void LayerData::addObject(Reference* objRef) {
		if (!objRef) return;
		perCellReferences.insert(objRef);
		g_ObjectLayerMap[objRef] = this;
		updateObject(objRef);
	}

	void LayerData::updateObject(Reference* objRef, bool forceRestore) {

		if (perCellReferences.find(objRef) == perCellReferences.end()) return;

		auto node = objRef ? objRef->sceneNode : nullptr;
		if (!node) return;

		for (auto& child : node->children) {
			if (child && child->isInstanceOfType(NI::RTTIStaticPtr::NiTriShape)) {

				auto triShape = static_cast<NI::TriShape*>(child.get());

				auto currMaterialProp = triShape->getMaterialProperty();

				if (currMaterialProp) {

					auto nodeColorData = getNodeColorData(triShape);

					auto layerColor = getLayerColor();
					auto layerMaterial = getLayerOverlayMaterial(currMaterialProp);
					auto layerVertexProp = getLayerVertexColorProperty();
					auto layerAlphaProp = getLayerAlphaProperty();

					auto currVertexProp = triShape->getVertexColorProperty();
					auto currAlphaProperty = triShape->getAlphaProperty();

					if (isOverlayActive && !forceRestore) {
						// Apply overlay material
						if (!nodeColorData->originalMaterial) {
							nodeColorData->originalMaterial = currMaterialProp;
						}
						triShape->setMaterialProperty(layerMaterial);

						// Apply vertex color prop
						if (!nodeColorData->originalVColorProperty) {
							nodeColorData->originalVColorProperty = currVertexProp;
						}
						triShape->setVertexColorProperty(layerVertexProp);
					}
					else {
						// Restore original material
						auto originalMaterial = nodeColorData->originalMaterial;
						if (originalMaterial) {
							triShape->setMaterialProperty(originalMaterial);
						}
						else if (layerMaterial == currMaterialProp) {
							triShape->detachPropertyByType(NI::PropertyType::Material);
						}

						// Restore original vertex color prop
						auto originalVertexProp = nodeColorData->originalVColorProperty;
						if (originalVertexProp) {
							triShape->setVertexColorProperty(originalVertexProp);
						}
						else if (layerVertexProp == currVertexProp) {
							triShape->detachPropertyByType(NI::PropertyType::VertexColor);
						}
					}

					if (isOverlayActive && isLayerHidden && !forceRestore) {
						// Apply transparency 
						if (!nodeColorData->originalAlphaProperty) {
							nodeColorData->originalAlphaProperty = currAlphaProperty;
						}

						triShape->setAlphaProperty(layerAlphaProp);

						layerMaterial->setAlpha(0.5f);
					}
					else {
						// Restore original alpha prop
						auto originalAlphaProp = nodeColorData->originalAlphaProperty;

						layerMaterial->setAlpha(1.0f);
						if (originalAlphaProp) {
							triShape->setAlphaProperty(originalAlphaProp);
						}
						else if (layerAlphaProp == currAlphaProperty) {
							triShape->detachPropertyByType(NI::PropertyType::Alpha);
						}
					}

					triShape->updateProperties();

					if (forceRestore) {
						// Clean up stored data
						removeNodeColorData(triShape);
					}
				}
			}
		}

		// Cull object if layer is hidden and overlay is not active
		bool isObjectCulled = isLayerHidden && !isOverlayActive && !forceRestore;
		node->setAppCulled(isObjectCulled);

		// Updates all children as well
		node->update();
	}

	void LayerData::refreshObjects() {
		for (auto objRef : perCellReferences) {
			updateObject(objRef);
		}

		se::cs::dialog::render_window::renderNextFrame();
	}

	void LayerData::moveObjectToLayer(Reference* objRef, LayerData* currentLayerInput) {
		if (!objRef) return;

		auto currentLayer = currentLayerInput ? currentLayerInput : getLayerByObject(objRef);

		if (currentLayer) {
			currentLayer->removeObject(objRef);
		}

		addObject(objRef);
	}

	void LayerData::moveSelectionToLayer() {
		auto selectionData = se::cs::dialog::render_window::SelectionData::get();
		for (auto target = selectionData->firstTarget; target; target = target->next) {
			auto objRef = target->reference;
			if (!objRef) {
				continue;
			}
			moveObjectToLayer(objRef);
		}
		selectionData->clear();
		se::cs::dialog::render_window::renderNextFrame();
	}

	void LayerData::clearLayer() {
		auto defaultLayer = getLayerById(0);
		
		// copy to avoid problems with modification during iteration
		auto objectsToMove = perCellReferences; 
		for (auto objRef : objectsToMove) {
			defaultLayer->moveObjectToLayer(objRef, this);
		}

		se::cs::dialog::render_window::renderNextFrame();
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

	std::unordered_map<size_t, LayerData*> GetLayers() {
		return g_LayersIdMap;
	}

	LayerData* getLayerById(size_t id) {
		if (id >= MAX_LAYERS || id < 0) return nullptr;
		auto it = g_LayersIdMap.find(id);
		if (it != g_LayersIdMap.end()) {
			return it->second;
		}
		return nullptr;
	}

	LayerData* getLayerByObject(Reference* obj)
	{
		if (!obj) return nullptr;
		auto it = g_ObjectLayerMap.find(obj);
		if (it != g_ObjectLayerMap.end()) {
			return it->second;
		}
		return nullptr;
	}

	size_t getNextLayerId() {
		size_t nextId = 0;
		while (g_LayersIdMap.find(nextId) != g_LayersIdMap.end()) {
			++nextId;
		}

		return nextId >= MAX_LAYERS ? MAX_LAYERS + 1 : nextId;
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

			// insert default layers
			for (int i = 0; i < (int)g_Layers.size(); ++i) {
				LVITEMA lvI = { 0 };
				lvI.mask = LVIF_TEXT;
				lvI.iItem = i;
				lvI.pszText = LPSTR_TEXTCALLBACK;
				ListView_InsertItem(hListView, &lvI);
			}

			hBtnAdd = CreateWindowExA(0, "BUTTON", "New Layer",
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

				LayerData* layer = g_Layers[pDIS->itemID];

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
				DrawTextA(pDIS->hDC, layer->layerName->c_str(), -1, &rcLabel, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

				InflateRect(&rcColor, -4, -4);
				HBRUSH hBrush = CreateSolidBrush(NIColorToRef(layer->getLayerColor()));
				FillRect(pDIS->hDC, &rcColor, hBrush);
				FrameRect(pDIS->hDC, &rcColor, (HBRUSH)GetStockObject(BLACK_BRUSH)); // Border
				DeleteObject(hBrush);

				UINT stateVis = DFCS_BUTTONCHECK | (!layer->isLayerHidden ? DFCS_CHECKED : 0);
				DrawFrameControl(pDIS->hDC, &rcVis, DFC_BUTTON, stateVis);

				UINT stateOver = DFCS_BUTTONCHECK | (layer->isOverlayActive ? DFCS_CHECKED : 0);
				DrawFrameControl(pDIS->hDC, &rcOver, DFC_BUTTON, stateOver);

				return TRUE;
			}
			break;
		}

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDC_ADD_LAYER_BTN) {
				auto nextId = getNextLayerId();
				if (g_Layers.size() < MAX_LAYERS && nextId < MAX_LAYERS) {
					LayerData* newLayer = new LayerData();
					newLayer->id = nextId;
					newLayer->layerName = new std::string(("Layer " + std::to_string(nextId)));
					auto randomColor = NI::Color{
						static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
						static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
						static_cast<float>(rand()) / static_cast<float>(RAND_MAX)
					};
					newLayer->setLayerColor(randomColor);
					g_Layers.push_back(newLayer);
					g_LayersIdMap[newLayer->id] = newLayer;

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

			// If clicked on column 1, 2, or 3 (Color, Vis, Overlay), cancel edit.
			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == LVN_BEGINLABELEDIT) {
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(hListView, &pt);

				LVHITTESTINFO hitInfo = { 0 };
				hitInfo.pt = pt;
				ListView_SubItemHitTest(hListView, &hitInfo);

				if (hitInfo.iSubItem != 0) {
					return TRUE; 
				}
				return FALSE; 
			}

			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == NM_RCLICK) {
				LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;

				POINT pt;
				GetCursorPos(&pt);
				POINT ptClient = pt;
				ScreenToClient(hListView, &ptClient);

				LVHITTESTINFO hitInfo = { 0 };
				hitInfo.pt = ptClient;
				ListView_SubItemHitTest(hListView, &hitInfo);

				if (hitInfo.iItem != -1 && hitInfo.iItem < (int)g_Layers.size()) {
					// Select the item being right-clicked
					ListView_SetItemState(hListView, hitInfo.iItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

					LayerData* layer = g_Layers[hitInfo.iItem];

					HMENU hPopup = CreatePopupMenu();
					AppendMenuA(hPopup, MF_STRING, IDM_LAYER_MOVE, "Move to layer");
					AppendMenuA(hPopup, MF_STRING, IDM_LAYER_CLEAR, "Clear layer");

					// Show menu
					int selected = TrackPopupMenu(hPopup, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
					DestroyMenu(hPopup);

					if (selected == IDM_LAYER_MOVE) {
						layer->moveSelectionToLayer();
					}
					else if (selected == IDM_LAYER_CLEAR) {
						if (MessageBoxA(hWnd, "Are you sure you want to clear this layer? All objects will be moved to Default.", "Clear Layer", MB_YESNO | MB_ICONWARNING) == IDYES) {
							layer->clearLayer();
						}
					}
				}
			}

			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == NM_CLICK) {
				LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;

				if (lpnmitem->iItem != -1 && lpnmitem->iItem < (int)g_Layers.size()) {
					LayerData* layer = g_Layers[lpnmitem->iItem];

					//color picker
					if (lpnmitem->iSubItem == 1) {
						CHOOSECOLORA cc = { 0 };
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hWnd;
						cc.lpCustColors = g_CustomColors;
						cc.rgbResult = NIColorToRef(layer->getLayerColor());
						cc.Flags = CC_FULLOPEN | CC_RGBINIT;

						if (ChooseColorA(&cc)) {
							layer->setLayerColor(RefToNIColor(cc.rgbResult));
							InvalidateRect(hListView, NULL, FALSE);
						}
					}

					// visibility toggle
					else if (lpnmitem->iSubItem == 2) {
						layer->isLayerHidden = !layer->isLayerHidden;
						InvalidateRect(hListView, NULL, FALSE);
					}

					// color overlay toggle
					else if (lpnmitem->iSubItem == 3) {
						layer->isOverlayActive = !layer->isOverlayActive;
						InvalidateRect(hListView, NULL, FALSE);
					}

					layer->refreshObjects();
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
						// Update name
						delete g_Layers[pDisp->item.iItem]->layerName;
						g_Layers[pDisp->item.iItem]->layerName = new std::string(pDisp->item.pszText);
						InvalidateRect(hListView, NULL, FALSE);
						return TRUE; 
					}
				}
			}

			if (lpnm->idFrom == IDC_LAYERS_LIST && lpnm->code == LVN_KEYDOWN) {
				LPNMLVKEYDOWN pnkd = (LPNMLVKEYDOWN)lParam;
				if (pnkd->wVKey == VK_DELETE) {
					int iItem = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
					if (iItem != -1 && iItem < (int)g_Layers.size()) {
						LayerData* l = g_Layers[iItem];
						// Prevent deleting default layers
						if (l->id == 0 || l->id == 1) {
							MessageBoxA(hWnd, "Cannot delete Default or Hidden layer.", "Error", MB_OK);
						}
						else {
							// Move objects to default before deleting
							l->clearLayer();

							delete g_Layers[iItem];
							g_Layers.erase(g_Layers.begin() + iItem);
							g_LayersIdMap.erase(l->id);

							ListView_DeleteItem(hListView, iItem);
						}
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

		if (g_Layers.empty()) {
			// Default Layer
			auto defaultLayer = new LayerData();
			defaultLayer->id = 0;
			defaultLayer->layerName = new std::string("Default");
			defaultLayer->setLayerColor({ 1.0f, 1.0f, 1.0f });
			defaultLayer->isLayerHidden = false;
			defaultLayer->isOverlayActive = false;
			g_Layers.push_back(defaultLayer);
			g_LayersIdMap[defaultLayer->id] = defaultLayer;

			// Hidden Layer
			auto hiddenLayer = new LayerData();
			hiddenLayer->id = 1;
			hiddenLayer->layerName = new std::string("Hidden");
			hiddenLayer->isLayerHidden = true;
			hiddenLayer->isOverlayActive = false;
			g_Layers.push_back(hiddenLayer);
			g_LayersIdMap[hiddenLayer->id] = hiddenLayer;
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