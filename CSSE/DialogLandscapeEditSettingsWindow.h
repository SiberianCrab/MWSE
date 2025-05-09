#pragma once

#include "MemoryUtil.h"

#include "CSDefines.h"
#include "NIDefines.h"

namespace se::cs::dialog::landscape_edit_settings_window {

	constexpr UINT DIALOG_ID = 203;

	constexpr UINT CONTROL_ID_EDIT_COLORS_CHECKBOX = 1008;
	constexpr UINT CONTROL_ID_EDIT_FALLOFF_EDIT = 1002;
	constexpr UINT CONTROL_ID_EDIT_RADIUS_EDIT = 1000;
	constexpr UINT CONTROL_ID_FLATTEN_VERTICES_CHECKBOX = 1006;
	constexpr UINT CONTROL_ID_SHOW_EDIT_RADIUS_CHECKBOX = 1007;
	constexpr UINT CONTROL_ID_SOFTEN_VERTICES_CHECKBOX = 1009;
	constexpr UINT CONTROL_ID_TEXTURE_LIST = 1492;
	constexpr UINT CONTROL_ID_ADD_TEXTURE_BUTTON = 1018;
	constexpr UINT CONTROL_ID_PREVIEW_TEXTURE_FRAME_STATIC = 1120;
	constexpr UINT CONTROL_ID_PREVIEW_TEXTURE_NAME_STATIC = 1493;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_RED_EDIT = 1213;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_RED_SPIN = 1130;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_GREEN_EDIT = 1214;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_GREEN_SPIN = 1131;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_BLUE_EDIT = 1215;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_BLUE_SPIN = 1132;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_SELECT_COLOR_BUTTON = 1134;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_PREVIEW_STATIC = 1133;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_RED_EDIT = 1502;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_RED_SPIN = 1505;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_GREEN_EDIT = 1503;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_GREEN_SPIN = 1506;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_BLUE_EDIT = 1504;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_BLUE_SPIN = 1507;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_SELECT_COLOR_BUTTON = 1137;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_PREVIEW_STATIC = 1136;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_ONE_STATIC = 1508;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_TWO_STATIC = 1509;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_THREE_STATIC = 1510;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_FOUR_STATIC = 1511;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_FIVE_STATIC = 1512;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_SIX_STATIC = 1513;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_SEVEN_STATIC = 1514;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_EIGHT_STATIC = 1515;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_NINE_STATIC = 1516;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_TEN_STATIC = 1517;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_ELEVEN_STATIC = 1518;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_TWELVE_STATIC = 1519;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_THIRTEEN_STATIC = 1520;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_FOURTEEN_STATIC = 1521;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_FIFTEEN_STATIC = 1522;
	constexpr UINT CONTROL_ID_CUSTOM_COLOR_SIXTEEN_STATIC = 1523;
	constexpr UINT CONTROL_ID_EXIT_EDITING_BUTTON = 2;
	constexpr UINT CONTROL_ID_PREVIEW_TEXTURE_BUTTON = 1058;

	// Custom IDs
	constexpr UINT CONTROL_ID_HEIGHT_GROUPBOX = 2000;
	constexpr UINT CONTROL_ID_EDIT_RADIUS_STATIC = 2001;
	constexpr UINT CONTROL_ID_EDIT_FALLOFF_STATIC = 2002;
	constexpr UINT CONTROL_ID_TEXTURE_GROUPBOX = 2003;
	constexpr UINT CONTROL_ID_SELECTED_TEXTURE_STATIC = 2004;
	constexpr UINT CONTROL_ID_VERTEX_COLOR_GROUPBOX = 2005;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_RED_STATIC = 2006;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_GREEN_STATIC = 2007;
	constexpr UINT CONTROL_ID_PRIMARY_COLOR_BLUE_STATIC = 2008;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_RED_STATIC = 2009;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_GREEN_STATIC = 2010;
	constexpr UINT CONTROL_ID_SECONDARY_COLOR_BLUE_STATIC = 2011;
	constexpr UINT CONTROL_ID_SHOW_PREVIEW_TEXTURE_BUTTON = 2012;

	using gWindowHandle = memory::ExternalGlobal<HWND, 0x6CE95C>;

	bool getEditLandscapeColor();
	void setEditLandscapeColor(bool value);
	bool getFlattenLandscapeVertices();
	void setFlattenLandscapeVertices(bool value);
	bool getSoftenLandscapeVertices();
	void setSoftenLandscapeVertices(bool value);

	LandTexture* getSelectedTexture();
	bool setSelectTexture(LandTexture* texture);

	bool incrementEditRadius();
	bool decrementEditRadius();

	using gLandscapeEditingEnabled = memory::ExternalGlobal<bool, 0x6CF792>;
	using gLandscapeModifyingVertices = memory::ExternalGlobal<bool, 0x6CF794>;

	bool getLandscapeEditingEnabled();
	void setLandscapeEditingEnabled(bool enabled, bool ifWindowOpen = false);

	void installPatches();
}
