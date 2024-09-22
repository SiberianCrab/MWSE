#pragma once

namespace se::cs::dialog::edit_birthsigns_window {

	constexpr UINT DIALOG_ID = 223;

	// Default IDs.
	constexpr UINT CONTROL_ID_COMBO = 1028;
	constexpr UINT CONTROL_ID_NEW_BUTTON = 1124;
	constexpr UINT CONTROL_ID_RENAME_BUTTON = 1134;
	constexpr UINT CONTROL_ID_DELETE_BUTTON = 1155;
	constexpr UINT CONTROL_ID_FULL_NAME_EDIT = 1029;
	constexpr UINT CONTROL_ID_SPELL_LIST = 1018;
	constexpr UINT CONTROL_ID_DESCRIPTION_EDIT = 1138;
	constexpr UINT CONTROL_ID_OK_BUTTON = 1;
	constexpr UINT CONTROL_ID_CONSTELLATION_IMAGE_BUTTON = 1044;


	// Custom IDs.
	constexpr UINT CONTROL_ID_ID_STATIC = 2000;
	constexpr UINT CONTROL_ID_FULL_NAME_STATIC = 2001;
	constexpr UINT CONTROL_ID_DESCRIPTION_STATIC = 2002;

	void installPatches();
}