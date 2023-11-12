#include "DialogLandscapeEditSettingsWindow.h"

#include "CSLandTexture.h"

#include "WinUIUtil.h"

#include "Settings.h"
#include "CSDataHandler.h"
#include "CSRecordHandler.h"
#include "CSRegion.h"

namespace se::cs::dialog::landscape_edit_settings_window {
	constexpr auto MIN_WIDTH = 430u;
	constexpr auto MIN_HEIGHT = 540u;


	namespace LandscapeEditFlag {
		enum LandscapeEditFlag : unsigned int {
			ShowEditRadius = 0x1,
			FlattenVertices = 0x2,
			EditColors = 0x4,
			SoftenVertices = 0x8,
		};
	}

	using gLandscapeEditFlags = memory::ExternalGlobal<unsigned int, 0x6CE9C8>;

	bool getLandscapeEditFlag(LandscapeEditFlag::LandscapeEditFlag flag) {
		return gLandscapeEditFlags::get() & flag;
	}

	void setLandscapeEditFlag(LandscapeEditFlag::LandscapeEditFlag flag, bool set) {
		auto& flags = gLandscapeEditFlags::get();
		if (set) {
			flags |= flag;
		}
		else {
			flags &= ~flag;
		}
	}

	bool getEditLandscapeColor() {
		return getLandscapeEditFlag(LandscapeEditFlag::EditColors);
	}

	void setEditLandscapeColor(bool set) {
		auto hWnd = gWindowHandle::get();

		setLandscapeEditFlag(LandscapeEditFlag::EditColors, set);
		CheckDlgButton(hWnd, CONTROL_ID_EDIT_COLORS_CHECKBOX, set ? BST_CHECKED : BST_UNCHECKED);

		if (set) {
			setFlattenLandscapeVertices(false);
			EnableWindow(GetDlgItem(hWnd, CONTROL_ID_FLATTEN_VERTICES_CHECKBOX), FALSE);
			setSoftenLandscapeVertices(false);
			EnableWindow(GetDlgItem(hWnd, CONTROL_ID_SOFTEN_VERTICES_CHECKBOX), FALSE);
		}
		else {
			EnableWindow(GetDlgItem(hWnd, CONTROL_ID_FLATTEN_VERTICES_CHECKBOX), TRUE);
			EnableWindow(GetDlgItem(hWnd, CONTROL_ID_SOFTEN_VERTICES_CHECKBOX), TRUE);
		}
	}

	bool getFlattenLandscapeVertices() {
		return getLandscapeEditFlag(LandscapeEditFlag::FlattenVertices);
	}

	void setFlattenLandscapeVertices(bool set) {
		auto hWnd = gWindowHandle::get();

		setLandscapeEditFlag(LandscapeEditFlag::FlattenVertices, set);
		CheckDlgButton(hWnd, CONTROL_ID_FLATTEN_VERTICES_CHECKBOX, set ? BST_CHECKED : BST_UNCHECKED);

		if (set) {
			setSoftenLandscapeVertices(false);
			setEditLandscapeColor(false);
		}
	}

	bool getSoftenLandscapeVertices() {
		return getLandscapeEditFlag(LandscapeEditFlag::SoftenVertices);
	}

	void setSoftenLandscapeVertices(bool set) {
		auto hWnd = gWindowHandle::get();

		setLandscapeEditFlag(LandscapeEditFlag::SoftenVertices, set);
		CheckDlgButton(hWnd, CONTROL_ID_SOFTEN_VERTICES_CHECKBOX, set ? BST_CHECKED : BST_UNCHECKED);

		if (set) {
			setFlattenLandscapeVertices(false);
			setEditLandscapeColor(false);
		}
	}

	LandTexture* getSelectedTexture() {
		auto hWnd = gWindowHandle::get();
		if (hWnd == NULL) {
			return nullptr;
		}

		auto textureList = GetDlgItem(hWnd, CONTROL_ID_TEXTURE_LIST);
		auto selected = ListView_GetNextItem(textureList, -1, LVNI_SELECTED);
		if (selected == -1) {
			return nullptr;
		}

		LVITEMA queryData = {};
		queryData.mask = LVIF_PARAM;
		queryData.iItem = selected;
		if (!ListView_GetItem(textureList, &queryData)) {
			return nullptr;
		}

		return reinterpret_cast<LandTexture*>(queryData.lParam);
	}

	bool setSelectTexture(LandTexture* landTexture) {
		return setSelectTexture(landTexture->texture);
	}

	bool setSelectTexture(NI::Texture* texture) {
		if (texture == nullptr) {
			return false;
		}

		auto hWnd = gWindowHandle::get();
		if (hWnd == NULL) {
			return false;
		}

		LVITEMA queryData = {};
		queryData.mask = LVIF_PARAM;
		auto textureList = GetDlgItem(hWnd, CONTROL_ID_TEXTURE_LIST);
		auto textureCount = ListView_GetItemCount(textureList);
		for (auto row = 0; row < textureCount; ++row) {
			queryData.iItem = row;
			if (!ListView_GetItem(textureList, &queryData)) {
				continue;
			}

			auto landTexture = reinterpret_cast<LandTexture*>(queryData.lParam);
			if (!landTexture) {
				continue;
			}

			if (landTexture->texture == texture) {
				ListView_SetItemState(textureList, row, LVIS_SELECTED, LVIS_SELECTED);
				ListView_EnsureVisible(textureList, row, TRUE);
				return true;
			}
		}

		return false;
	}


	bool incrementEditRadius() {
		auto hWnd = gWindowHandle::get();
		if (hWnd == NULL) {
			return false;
		}

		auto radius = winui::GetDlgItemSignedInt(hWnd, CONTROL_ID_EDIT_RADIUS_EDIT).value_or(1);
		radius = std::min(radius + 1, 30);
		SetDlgItemInt(hWnd, CONTROL_ID_EDIT_RADIUS_EDIT, radius, FALSE);

		return true;
	}

	bool decrementEditRadius() {
		auto hWnd = gWindowHandle::get();
		if (hWnd == NULL) {
			return false;
		}

		auto radius = winui::GetDlgItemSignedInt(hWnd, CONTROL_ID_EDIT_RADIUS_EDIT).value_or(1);
		radius = std::max(radius - 1, 1);
		SetDlgItemInt(hWnd, CONTROL_ID_EDIT_RADIUS_EDIT, radius, FALSE);

		return true;
	}

	bool getLandscapeEditingEnabled() {
		return gLandscapeEditingEnabled::get();
	}

	void setLandscapeEditingEnabled(bool enabled, bool ifWindowOpen) {
		if (ifWindowOpen) {
			enabled = gWindowHandle::get() != NULL;
		}
		gLandscapeEditingEnabled::set(enabled);
	}

	void restoreTextureListColomnWidths(HWND hWnd) {
		const auto textureList = GetDlgItem(hWnd, CONTROL_ID_TEXTURE_LIST);

		ListView_SetColumnWidth(textureList, 0, settings.landscape_window.column_id.width);
		ListView_SetColumnWidth(textureList, 1, settings.landscape_window.column_used.width);
		ListView_SetColumnWidth(textureList, 2, settings.landscape_window.column_filename.width);

	}

	void saveTextureListColomnWidths(HWND hWnd) {
		const auto textureList = GetDlgItem(hWnd, CONTROL_ID_TEXTURE_LIST);

		settings.landscape_window.column_id.width = ListView_GetColumnWidth(textureList, 0);
		settings.landscape_window.column_used.width = ListView_GetColumnWidth(textureList, 1);
		settings.landscape_window.column_filename.width = ListView_GetColumnWidth(textureList, 2);
	}

	void togglePreviewTextureShown(HWND hWnd, int id) {
		settings.landscape_window.show_preview_enabled = !settings.landscape_window.show_preview_enabled;

		auto hDlgSelectedTextureStatic = GetDlgItem(hWnd, CONTROL_ID_SELECTED_TEXTURE_STATIC);
		auto hDlgPreviewTextureFrameStatic = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_FRAME_STATIC);
		auto hDlgPreviewTextureImage = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_BUTTON);

		int width = settings.landscape_window.size.width;
		bool isVisible;

		if (settings.landscape_window.show_preview_enabled) {
			width += 270;
			isVisible = TRUE;
		}
		else {
			width -= 270;
			isVisible = FALSE;
		}

		// hide/unhide the preview texture controls
		ShowWindow(hDlgSelectedTextureStatic, isVisible);
		ShowWindow(hDlgPreviewTextureFrameStatic, isVisible);
		ShowWindow(hDlgPreviewTextureImage, isVisible);

		SetWindowPos(hWnd, NULL, 0, 0, width, settings.landscape_window.size.height, SWP_NOMOVE);

		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_ERASENOW | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	//
	// Patch: Extend Render Window message handling.
	//

	static std::optional<LRESULT> PatchDialogProc_OverrideResult = {};

	void PatchDialogProc_BeforeDestroy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		saveTextureListColomnWidths(hWnd);
		settings.landscape_window.size.width -= IsDlgButtonChecked(hWnd, CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON) ? 270 : 0;
	}

	void PatchDialogProc_AfterDestroy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		// Cleanup global handle address so we can rely on it being NULL.
		gWindowHandle::set(0x0);
	}

	void PatchDialogProc_BeforeCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		const auto command = HIWORD(wParam);
		const auto id = LOWORD(wParam);
		switch (command) {
		case BN_CLICKED:
			switch (id) {
			case CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON:
				togglePreviewTextureShown(hWnd, id);
				break;
			}
			break;
		}
	}

	std::optional<LRESULT> forcedReturnType = {};

	void PatchDialogProc_AfterInitialize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		using se::cs::winui::AddStyles;
		using se::cs::winui::RemoveStyles;
		using se::cs::winui::SetWindowIdByValue;

		restoreTextureListColomnWidths(hWnd);

		// Give IDs to controls that don't normally have one.
		SetWindowIdByValue(hWnd, "Height", CONTROL_ID_HEIGHT_GROUPBOX);
		SetWindowIdByValue(hWnd, "Edit Radius:", CONTROL_ID_EDIT_RADIUS_STATIC);
		SetWindowIdByValue(hWnd, "Edit Falloff %:", CONTROL_ID_EDIT_FALLOFF_STATIC);
		SetWindowIdByValue(hWnd, "Texture", CONTROL_ID_TEXTURE_GROUPBOX);
		SetWindowIdByValue(hWnd, "Selected\nTexture:", CONTROL_ID_SELECTED_TEXTURE_STATIC);
		SetWindowIdByValue(hWnd, "Vertex Color", CONTROL_ID_VERTEX_COLOR_GROUPBOX);
		SetWindowIdByValue(hWnd, "R", CONTROL_ID_PRIMARY_COLOR_RED_STATIC);
		SetWindowIdByValue(hWnd, "G", CONTROL_ID_PRIMARY_COLOR_GREEN_STATIC);
		SetWindowIdByValue(hWnd, "B", CONTROL_ID_PRIMARY_COLOR_BLUE_STATIC);
		SetWindowIdByValue(hWnd, "R", CONTROL_ID_SECONDARY_COLOR_RED_STATIC);
		SetWindowIdByValue(hWnd, "G", CONTROL_ID_SECONDARY_COLOR_GREEN_STATIC);
		SetWindowIdByValue(hWnd, "B", CONTROL_ID_SECONDARY_COLOR_BLUE_STATIC);

		RemoveStyles(hWnd, DS_MODALFRAME); // | WS_SYSMENU
		//AddStyles(hWnd, WS_POPUP | WS_CAPTION | WS_SIZEBOX);

		auto hInstance = (HINSTANCE)GetWindowLongA(hWnd, GWLP_HINSTANCE);
		auto font = SendMessageA(hWnd, WM_GETFONT, FALSE, FALSE);

		auto hDlgShowPreviewTextureButton = CreateWindowExA(NULL, WC_BUTTON, "Show Preview", BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_CHILD | WS_VISIBLE | WS_GROUP, 0, 0, 0, 0, hWnd, (HMENU)CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON, hInstance, NULL);
		SendMessageA(hDlgShowPreviewTextureButton, WM_SETFONT, font, MAKELPARAM(TRUE, FALSE));

		// Hide the preview texture controls
		if (!settings.landscape_window.show_preview_enabled) {
			auto hDlgSelectedTextureStatic = GetDlgItem(hWnd, CONTROL_ID_SELECTED_TEXTURE_STATIC);
			ShowWindow(hDlgSelectedTextureStatic, FALSE);

			auto hDlgPreviewTextureFrameStatic = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_FRAME_STATIC);
			ShowWindow(hDlgPreviewTextureFrameStatic, FALSE);

			auto hDlgPreviewTextureImage = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_BUTTON);
			ShowWindow(hDlgPreviewTextureImage, FALSE);
		}
		else {
			Button_SetCheck(GetDlgItem(hWnd, CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON), settings.landscape_window.show_preview_enabled);
		}

		// Change the selected texture static to be a single line
		SetDlgItemText(hWnd, CONTROL_ID_SELECTED_TEXTURE_STATIC, "Selected Texture:");

		// RGBs with ':'
		SetDlgItemText(hWnd, CONTROL_ID_PRIMARY_COLOR_RED_STATIC, "R:");
		SetDlgItemText(hWnd, CONTROL_ID_PRIMARY_COLOR_GREEN_STATIC, "G:");
		SetDlgItemText(hWnd, CONTROL_ID_PRIMARY_COLOR_BLUE_STATIC, "B:");
		SetDlgItemText(hWnd, CONTROL_ID_SECONDARY_COLOR_RED_STATIC, "R:");
		SetDlgItemText(hWnd, CONTROL_ID_SECONDARY_COLOR_GREEN_STATIC, "G:");
		SetDlgItemText(hWnd, CONTROL_ID_SECONDARY_COLOR_BLUE_STATIC, "B:");

		// Change element style
		auto setControlStyle = [](HWND hCtrl, DWORD addStyle, DWORD removeStyle = 0) {
			DWORD style = GetWindowLongPtr(hCtrl, GWL_STYLE);
			SetWindowLongPtr(hCtrl, GWL_STYLE, (style & ~removeStyle) | addStyle);
		};

			setControlStyle(GetDlgItem(hWnd, CONTROL_ID_EDIT_RADIUS_STATIC), SS_RIGHT, SS_TYPEMASK);
			setControlStyle(GetDlgItem(hWnd, CONTROL_ID_EDIT_FALLOFF_STATIC), SS_RIGHT, SS_TYPEMASK);
			setControlStyle(GetDlgItem(hWnd, CONTROL_ID_SELECTED_TEXTURE_STATIC), SS_LEFT | SS_TYPEMASK);
			setControlStyle(GetDlgItem(hWnd, CONTROL_ID_EDIT_COLORS_CHECKBOX), BS_LEFTTEXT | BS_RIGHT);

		// Restore size and position
		const auto& settingsSize = settings.landscape_window.size;
		const auto width = std::max(settingsSize.width, MIN_WIDTH);
		const auto height = std::max(settingsSize.height, MIN_HEIGHT);
		const auto x = settings.landscape_window.x_position;
		const auto y = settings.landscape_window.y_position;

		MoveWindow(hWnd, x, y, width, height, FALSE);
		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

	void PatchDialogProc_GetMinMaxInfo(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		const auto showPreviewImagePadding = IsDlgButtonChecked(hWnd, CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON) ? 270 : 0;
		const auto info = (LPMINMAXINFO)lParam;
		info->ptMinTrackSize.x = MIN_WIDTH + showPreviewImagePadding;
		info->ptMinTrackSize.y = MIN_HEIGHT;

		forcedReturnType = 0;
	}

	void PatchDialogProc_AfterMove(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		int short xPos = LOWORD(lParam);
		int short yPos = HIWORD(lParam);

		settings.landscape_window.x_position = xPos - 8;
		settings.landscape_window.y_position = yPos - 31;
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

		constexpr auto CUSTOM_COLOR_WIDTH = 40;
		constexpr auto CUSTOM_COLOR_HEIGHT = CUSTOM_COLOR_WIDTH / 2;
		constexpr auto CUSTOM_COLOR_SECTION_WIDTH = CUSTOM_COLOR_WIDTH * 8 + BIG_PADDING * 8;
		constexpr auto COLOR_PREVIEW_HEIGHT = COMBO_HEIGHT * 2 + BASIC_PADDING;

		constexpr auto HEIGHT_SECTION_HEIGHT = BIG_PADDING * 4 + COMBO_HEIGHT * 2 + BASIC_PADDING;
		constexpr auto VERTEX_COLOR_SECTION_HEIGHT = COMBO_HEIGHT * 5 + BASIC_PADDING * 2 + BIG_PADDING * 4 + CUSTOM_COLOR_HEIGHT * 2;
		constexpr auto BOTTOM_SECTION_HEIGHT = COMBO_HEIGHT + WINDOW_EDGE_PADDING * 2;

		constexpr auto BUTTON_WIDTH = 90;
		constexpr auto EDIT_FIELD_WIDTH = 40;
		constexpr auto EDIT_COLORS_CHECKBOX_WIDTH = 90;
		constexpr auto SHOW_EDIT_RADIUS_CHECKBOX_WIDTH = 130;
		constexpr auto FLATTEN_VERTICES_CHECKBOX_WIDTH = 120;
		constexpr auto SOFTEN_VERTICES_CHECKBOX_WIDTH = 120;

		constexpr auto PREVIEW_TEXTURE_NAME_STATIC_WIDTH = 150;
		constexpr auto PREVIEW_TEXTURE_BOX = 256;
		constexpr auto PREVIEW_TEXTURE_FRAME_BOX = PREVIEW_TEXTURE_BOX + STATIC_COMBO_OFFSET;

		constexpr auto RGB_WIDTH = EDIT_FIELD_WIDTH / 2;
		constexpr auto VERTEX_EDIT_WIDTH = EDIT_FIELD_WIDTH;
		constexpr auto SPIN_WIDTH = EDIT_FIELD_WIDTH / 2;

		constexpr auto COLOR_PREVIEW_GROUP_OFFSET = RGB_WIDTH + BASIC_PADDING + VERTEX_EDIT_WIDTH + SPIN_WIDTH + BIG_PADDING;
		constexpr auto CURRENT_COLOR_SECTION_WIDTH = COLOR_PREVIEW_GROUP_OFFSET + BUTTON_WIDTH;
	}

	void ResizeCustomColorStatic(HWND hParent, int iDlgStatic, int& x, int y) {
		using namespace ResizeConstants;

		auto hDlgStatic = GetDlgItem(hParent, iDlgStatic);
		MoveWindow(hDlgStatic, x, y, CUSTOM_COLOR_WIDTH, CUSTOM_COLOR_HEIGHT, FALSE);

		x += CUSTOM_COLOR_WIDTH + BIG_PADDING;
	}

	void ResizeStaticEditSpin(HWND hParent, int iDlgStatic, int iDlgEdit, int iDlgSpin, int x, int& y) {
		using namespace ResizeConstants;

		auto hDlgStatic = GetDlgItem(hParent, iDlgStatic);
		MoveWindow(hDlgStatic, x, y + STATIC_COMBO_OFFSET, RGB_WIDTH, STATIC_HEIGHT, FALSE);

		auto hDlgEdit = GetDlgItem(hParent, iDlgEdit);
		MoveWindow(hDlgEdit, x + BASIC_PADDING + RGB_WIDTH, y, VERTEX_EDIT_WIDTH, COMBO_HEIGHT, FALSE);

		auto hDlgSpin = GetDlgItem(hParent, iDlgSpin);
		MoveWindow(hDlgSpin, x + RGB_WIDTH + VERTEX_EDIT_WIDTH, y, SPIN_WIDTH, COMBO_HEIGHT, FALSE);

		y += COMBO_HEIGHT + BASIC_PADDING;
	}

#define ResizeStaticEditSpinHelper(hParent, primaryOrSecondary, color, x, y) ResizeStaticEditSpin(hParent, CONTROL_ID_##primaryOrSecondary##_COLOR_##color##_STATIC, CONTROL_ID_##primaryOrSecondary##_COLOR_##color##_EDIT, CONTROL_ID_##primaryOrSecondary##_COLOR_##color##_SPIN, x, y)

	void PatchDialogProc_BeforeSize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		using namespace ResizeConstants;

		const auto showPreviewImagePadding = IsDlgButtonChecked(hWnd, CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON) ? 270 : 0;

		const auto clientWidth = LOWORD(lParam);
		const auto clientHeight = HIWORD(lParam);
		const auto sectionWidth = clientWidth - WINDOW_EDGE_PADDING * 2 - showPreviewImagePadding;


		// Height Groupbox
		{
			auto currentX = WINDOW_EDGE_PADDING;
			auto currentY = WINDOW_EDGE_PADDING;

			auto heightGroupbox = GetDlgItem(hWnd, CONTROL_ID_HEIGHT_GROUPBOX);
			MoveWindow(heightGroupbox, currentX, currentY - BIG_PADDING, sectionWidth, HEIGHT_SECTION_HEIGHT, FALSE);

			currentX += BIG_PADDING;
			currentY += BIG_PADDING * 2;

			auto editRadiusStatic = GetDlgItem(hWnd, CONTROL_ID_EDIT_RADIUS_STATIC);
			MoveWindow(editRadiusStatic, currentX, currentY + STATIC_COMBO_OFFSET, BUTTON_WIDTH, STATIC_HEIGHT, FALSE);

			currentX += BASIC_PADDING * 2 + BUTTON_WIDTH;

			auto editRadiusEdit = GetDlgItem(hWnd, CONTROL_ID_EDIT_RADIUS_EDIT);
			MoveWindow(editRadiusEdit, currentX, currentY, EDIT_FIELD_WIDTH, COMBO_HEIGHT, FALSE);

			currentX += BIG_PADDING + EDIT_FIELD_WIDTH;

			auto flattenVerticesCheckbox = GetDlgItem(hWnd, CONTROL_ID_FLATTEN_VERTICES_CHECKBOX);
			MoveWindow(flattenVerticesCheckbox, currentX, currentY + STATIC_COMBO_OFFSET, FLATTEN_VERTICES_CHECKBOX_WIDTH, STATIC_HEIGHT, FALSE);

			auto softenVerticesCheckbox = GetDlgItem(hWnd, CONTROL_ID_SOFTEN_VERTICES_CHECKBOX);
			MoveWindow(softenVerticesCheckbox, currentX + FLATTEN_VERTICES_CHECKBOX_WIDTH, currentY + STATIC_COMBO_OFFSET, SOFTEN_VERTICES_CHECKBOX_WIDTH, STATIC_HEIGHT, FALSE);

			currentX -= BASIC_PADDING * 2 + BIG_PADDING + BUTTON_WIDTH + EDIT_FIELD_WIDTH;
			currentY += COMBO_HEIGHT + BASIC_PADDING;

			auto editFallofEdit = GetDlgItem(hWnd, CONTROL_ID_EDIT_FALLOFF_EDIT);
			MoveWindow(editFallofEdit, currentX + BASIC_PADDING * 2 + BUTTON_WIDTH, currentY, EDIT_FIELD_WIDTH, COMBO_HEIGHT, FALSE);

			currentY += STATIC_COMBO_OFFSET;

			auto editFallofStatic = GetDlgItem(hWnd, CONTROL_ID_EDIT_FALLOFF_STATIC);
			MoveWindow(editFallofStatic, currentX, currentY, BUTTON_WIDTH, STATIC_HEIGHT, FALSE);

			currentX += BASIC_PADDING * 2 + BIG_PADDING + BUTTON_WIDTH + EDIT_FIELD_WIDTH + (FLATTEN_VERTICES_CHECKBOX_WIDTH + SOFTEN_VERTICES_CHECKBOX_WIDTH - SHOW_EDIT_RADIUS_CHECKBOX_WIDTH) / 2;

			auto showEditRadiusCheckbox = GetDlgItem(hWnd, CONTROL_ID_SHOW_EDIT_RADIUS_CHECKBOX);
			MoveWindow(showEditRadiusCheckbox, currentX, currentY, SHOW_EDIT_RADIUS_CHECKBOX_WIDTH, STATIC_HEIGHT, FALSE);
		}

		// Texture Section
		{
			auto currentX = WINDOW_EDGE_PADDING;
			auto currentY = WINDOW_EDGE_PADDING + HEIGHT_SECTION_HEIGHT;
			const auto TEXTURE_SECTION_HEIGHT = clientHeight - HEIGHT_SECTION_HEIGHT - VERTEX_COLOR_SECTION_HEIGHT - BOTTOM_SECTION_HEIGHT - BIG_PADDING * 3;

			auto textureGroupbox = GetDlgItem(hWnd, CONTROL_ID_TEXTURE_GROUPBOX);
			MoveWindow(textureGroupbox, currentX, currentY, sectionWidth, TEXTURE_SECTION_HEIGHT, FALSE);

			currentX += WINDOW_EDGE_PADDING;

			auto TEXTURE_LIST_WIDTH = sectionWidth - WINDOW_EDGE_PADDING * 2;
			const auto TEXTURE_LIST_HEIGHT = TEXTURE_SECTION_HEIGHT - COMBO_HEIGHT * 2 - BIG_PADDING * 2 - BASIC_PADDING;

			// Texture prewiew section offset
			currentX += TEXTURE_LIST_WIDTH + WINDOW_EDGE_PADDING * 2;

			auto selectedTextureStatic = GetDlgItem(hWnd, CONTROL_ID_SELECTED_TEXTURE_STATIC);
			MoveWindow(selectedTextureStatic, currentX, currentY, PREVIEW_TEXTURE_NAME_STATIC_WIDTH, STATIC_HEIGHT, FALSE);

			currentY += STATIC_HEIGHT + BIG_PADDING;

			auto previewTextureImage = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_BUTTON);
			MoveWindow(previewTextureImage, currentX + BASIC_PADDING, currentY + BASIC_PADDING, PREVIEW_TEXTURE_BOX, PREVIEW_TEXTURE_BOX, FALSE);

			auto previewTextureFrameStatic = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_FRAME_STATIC);
			MoveWindow(previewTextureFrameStatic, currentX, currentY, PREVIEW_TEXTURE_FRAME_BOX, PREVIEW_TEXTURE_FRAME_BOX, FALSE);

			currentX -= TEXTURE_LIST_WIDTH + WINDOW_EDGE_PADDING * 2;
			currentY -= STATIC_HEIGHT + BIG_PADDING;
			// Texture prewiew section offset end

			currentY += COMBO_HEIGHT;

			auto textureList = GetDlgItem(hWnd, CONTROL_ID_TEXTURE_LIST);
			MoveWindow(textureList, currentX, currentY, TEXTURE_LIST_WIDTH, TEXTURE_LIST_HEIGHT, FALSE);

			currentY += TEXTURE_LIST_HEIGHT + BIG_PADDING;

			auto addTextureButton = GetDlgItem(hWnd, CONTROL_ID_ADD_TEXTURE_BUTTON);
			MoveWindow(addTextureButton, currentX, currentY, BUTTON_WIDTH, COMBO_HEIGHT, FALSE);

			auto previewTextureNameStatic = GetDlgItem(hWnd, CONTROL_ID_PREVIEW_TEXTURE_NAME_STATIC);
			MoveWindow(previewTextureNameStatic, currentX + BUTTON_WIDTH + BASIC_PADDING, currentY + STATIC_COMBO_OFFSET, CUSTOM_COLOR_SECTION_WIDTH + BIG_PADDING - BUTTON_WIDTH * 2 - BASIC_PADDING * 2, STATIC_HEIGHT, FALSE);

			currentX += CUSTOM_COLOR_SECTION_WIDTH + BIG_PADDING - BUTTON_WIDTH;

			auto showPreviewTextureButton = GetDlgItem(hWnd, CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON);
			MoveWindow(showPreviewTextureButton, currentX, currentY, BUTTON_WIDTH, COMBO_HEIGHT, FALSE);
		}

		// Vertex Color Section
		{
			auto currentX = WINDOW_EDGE_PADDING;
			auto currentY = clientHeight - VERTEX_COLOR_SECTION_HEIGHT - BOTTOM_SECTION_HEIGHT;

			auto vertexColorGroupbox = GetDlgItem(hWnd, CONTROL_ID_VERTEX_COLOR_GROUPBOX);
			MoveWindow(vertexColorGroupbox, currentX, currentY, sectionWidth, VERTEX_COLOR_SECTION_HEIGHT, FALSE);

			currentX += WINDOW_EDGE_PADDING;

			auto editColorsButton = GetDlgItem(hWnd, CONTROL_ID_EDIT_COLORS_CHECKBOX);
			MoveWindow(editColorsButton, currentX + CUSTOM_COLOR_SECTION_WIDTH - EDIT_COLORS_CHECKBOX_WIDTH, currentY + STATIC_COMBO_OFFSET * 2 + COMBO_HEIGHT / 2, EDIT_COLORS_CHECKBOX_WIDTH, STATIC_HEIGHT, FALSE);

			currentY += COMBO_HEIGHT * 2;

			auto primaryColorPreviewStatic = GetDlgItem(hWnd, CONTROL_ID_PRIMARY_COLOR_PREVIEW_STATIC);
			MoveWindow(primaryColorPreviewStatic, currentX + COLOR_PREVIEW_GROUP_OFFSET, currentY, BUTTON_WIDTH, COLOR_PREVIEW_HEIGHT, FALSE);

			ResizeStaticEditSpinHelper(hWnd, PRIMARY, RED, currentX, currentY);
			ResizeStaticEditSpinHelper(hWnd, PRIMARY, GREEN, currentX, currentY);
			ResizeStaticEditSpinHelper(hWnd, PRIMARY, BLUE, currentX, currentY);

			auto primaryColorSelectColorButton = GetDlgItem(hWnd, CONTROL_ID_PRIMARY_COLOR_SELECT_COLOR_BUTTON);
			MoveWindow(primaryColorSelectColorButton, currentX + COLOR_PREVIEW_GROUP_OFFSET, currentY - COMBO_HEIGHT - BASIC_PADDING, BUTTON_WIDTH, COMBO_HEIGHT, FALSE);

			currentX += CUSTOM_COLOR_SECTION_WIDTH / 2 + (CUSTOM_COLOR_SECTION_WIDTH / 2 - CURRENT_COLOR_SECTION_WIDTH);
			currentY = clientHeight - VERTEX_COLOR_SECTION_HEIGHT - BOTTOM_SECTION_HEIGHT + COMBO_HEIGHT * 2;

			auto secondaryColorPreviewStatic = GetDlgItem(hWnd, CONTROL_ID_SECONDARY_COLOR_PREVIEW_STATIC);
			MoveWindow(secondaryColorPreviewStatic, currentX + COLOR_PREVIEW_GROUP_OFFSET, currentY, BUTTON_WIDTH, COLOR_PREVIEW_HEIGHT, FALSE);

			ResizeStaticEditSpinHelper(hWnd, SECONDARY, RED, currentX, currentY);
			ResizeStaticEditSpinHelper(hWnd, SECONDARY, GREEN, currentX, currentY);
			ResizeStaticEditSpinHelper(hWnd, SECONDARY, BLUE, currentX, currentY);

			auto secondaryColorSelectColorButton = GetDlgItem(hWnd, CONTROL_ID_SECONDARY_COLOR_SELECT_COLOR_BUTTON);
			MoveWindow(secondaryColorSelectColorButton, currentX + COLOR_PREVIEW_GROUP_OFFSET, currentY - COMBO_HEIGHT - BASIC_PADDING, BUTTON_WIDTH, COMBO_HEIGHT, FALSE);

			currentX = WINDOW_EDGE_PADDING * 2 + BIG_PADDING;
			currentY += BIG_PADDING;

			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_ONE_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_TWO_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_THREE_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_FOUR_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_FIVE_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_SIX_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_SEVEN_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_EIGHT_STATIC, currentX, currentY);

			currentX = WINDOW_EDGE_PADDING * 2 + BIG_PADDING;
			currentY += CUSTOM_COLOR_HEIGHT + BIG_PADDING;

			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_NINE_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_TEN_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_ELEVEN_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_TWELVE_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_THIRTEEN_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_FOURTEEN_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_FIFTEEN_STATIC, currentX, currentY);
			ResizeCustomColorStatic(hWnd, CONTROL_ID_CUSTOM_COLOR_SIXTEEN_STATIC, currentX, currentY);
		}

		// Bottom Section
		{
			auto currentX = WINDOW_EDGE_PADDING * 2 + BIG_PADDING + (CUSTOM_COLOR_SECTION_WIDTH - BIG_PADDING) / 2 - BUTTON_WIDTH;
			auto currentY = clientHeight - BOTTOM_SECTION_HEIGHT + WINDOW_EDGE_PADDING;

			auto exitEditingButton = GetDlgItem(hWnd, CONTROL_ID_EXIT_EDITING_BUTTON);
			MoveWindow(exitEditingButton, currentX, currentY, BUTTON_WIDTH * 2, COMBO_HEIGHT, FALSE);
		}

		RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_ERASENOW | RDW_INVALIDATE | RDW_ALLCHILDREN);

		// Store window size for later restoration.
		SIZE winSize = {};
		if (winui::GetWindowSize(hWnd, winSize)) {
			settings.landscape_window.size = winSize;
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
			break;
		case WM_COMMAND:
			PatchDialogProc_BeforeCommand(hWnd, msg, wParam, lParam);
		}

		if (PatchDialogProc_OverrideResult) {
			return PatchDialogProc_OverrideResult.value();
		}
		// Call original function.
		const auto CS_RenderWindowDialogProc = reinterpret_cast<WNDPROC>(0x44D470);
		auto vanillaResult = CS_RenderWindowDialogProc(hWnd, msg, wParam, lParam);

		switch (msg) {
		case WM_DESTROY:
			PatchDialogProc_AfterDestroy(hWnd, msg, wParam, lParam);
			break;
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

		// Patch: Extend Render Window message handling.
		genJumpEnforced(0x4036A7, 0x44D470, reinterpret_cast<DWORD>(PatchDialogProc));
	}

}
