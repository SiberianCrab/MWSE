#pragma once

#include "MemoryUtil.h"

namespace se::cs::dialog::edit_leveled_creature_object_window {

	constexpr UINT DIALOG_ID = 168;

	constexpr UINT CONTROL_ID_ID_EDIT = 1028;
	constexpr UINT CONTROL_ID_CALCULATE_LEVELS_CHECKBOX = 1007;
	constexpr UINT CONTROL_ID_CHANCE_NONE_EDIT = 1030;
	constexpr UINT CONTROL_ID_LEVELED_LIST = 1593;
	constexpr UINT CONTROL_ID_OK_BUTTON = 1;
	constexpr UINT CONTROL_ID_CANCEL_BUTTON = 2;
	constexpr UINT CONTROL_ID_BLOCKED_CHECKBOX = 1684;

	// Custom IDs.
	constexpr UINT CONTROL_ID_ID_STATIC = 2000;
	constexpr UINT CONTROL_ID_CHANCE_NONE_STATIC = 2001;

	void installPatches();
}
