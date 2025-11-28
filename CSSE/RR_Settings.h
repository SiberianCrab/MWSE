#pragma once

namespace se::cs {

	constexpr int RR_BASIC_PADDING = 2;

	// Windows GUI scale modifier
	constexpr double RR_WIN_GUI_Scale = 1.33;

	// Font 08 = 16 | Font 10 = 24 (doest't look good) | Font 12 = 32
	constexpr int RR_Toolbar_Button = 32;
	constexpr int RR_Toolbar_Button_Count = 16;

	//08-12 Font Dependant Settings
		//ResizeConstants
			//Font 08 = 13 | Font 10 = 16 | Font 12 = 20
			constexpr int RR_Window_08_12_STATIC_HEIGHT = static_cast<int>(20 * RR_WIN_GUI_Scale);

	//08-10 Font Dependant Settings
		//ResizeConstants
			//Font 08 = 13 | Font 10 = 16
			constexpr int RR_Window_08_10_STATIC_HEIGHT = static_cast<int>(16 * RR_WIN_GUI_Scale);

	//DialogDialogueWindow.cpp Font Dependant Settings
		//Window Size
			//Font 08 = 1130u | Font 10 = 1240u
			constexpr unsigned int RR_DialogDialogueWindow_MIN_WIDTH = static_cast<unsigned int>(1240u * RR_WIN_GUI_Scale);
			//Font 08 = 640u | Font 10 = 820u
			constexpr unsigned int RR_DialogDialogueWindow_MIN_HEIGHT = static_cast<unsigned int>(820u * RR_WIN_GUI_Scale);

	//ResizeConstants
			//Font 08 = 250 | Font 10 = 298
			constexpr int RR_DialogDialogueWindow_LEFT_SECTION_WIDTH = static_cast<int>(298 * RR_WIN_GUI_Scale);
			//Font 08 = 150 | Font 10 = 200
			constexpr int RR_DialogDialogueWindow_BOTTOM_RIGHT_SECTION_WIDTH = static_cast<int>(200 * RR_WIN_GUI_Scale);
			//Font 08 = 66 | Font 10 = 80
			constexpr int RR_DialogDialogueWindow_CONDITION_STATIC_WIDTH = static_cast<int>(80 * RR_WIN_GUI_Scale);
			//Font 08 = 400 | Font 10 = 500 | Font 12 = ?
			constexpr int RR_DialogDialogueWindow_BOTTOM_SECTION_HEIGHT = static_cast<int>(500 * RR_WIN_GUI_Scale);
			//Font 08 = 30 | Font 10 = 32
			constexpr int RR_DialogDialogueWindow_TEXT_COUNTER_WIDTH = static_cast<int>(32 * RR_WIN_GUI_Scale);

	//DialogScriptEditorWindow.cpp Font Dependant Settings
		//Font Size
			//Font 08 = 20 | Font 10 = 22
			constexpr int RR_DialogScriptEditorWindow_FONT_SIZE = 22;

}