#pragma once

namespace se::cs {

	//08-12 Font Dependant Settings
		//ResizeConstants
			//Font 08 = 13 | Font 10 = 16 | Font 12 = 20
			constexpr auto Window_08_12_STATIC_HEIGHT = 20;

	//08-10 Font Dependant Settings
		//ResizeConstants
			//Font 08 = 13 | Font 10 = 16
			constexpr auto Window_08_10_STATIC_HEIGHT = 16;

	//DialogDialogueWindow.cpp Font Dependant Settings
		//Window Size
			//Font 08 = 1130u | Font 10 = 1240u
			constexpr auto DialogDialogueWindow_MIN_WIDTH = 1240u;
			//Font 08 = 640u | Font 10 = 820u
			constexpr auto DialogDialogueWindow_MIN_HEIGHT = 820u;

		//ResizeConstants
			//Font 08 = 250 | Font 10 = 298
			constexpr auto DialogDialogueWindow_LEFT_SECTION_WIDTH = 298;
			//Font 08 = 150 | Font 10 = 200
			constexpr auto DialogDialogueWindow_BOTTOM_RIGHT_SECTION_WIDTH = 200;
			//Font 08 = 66 | Font 10 = 80
			constexpr auto DialogDialogueWindow_CONDITION_STATIC_WIDTH = 80;
			//Font 08 = 400 | Font 10 = 500 | Font 12 = ?
			constexpr auto DialogDialogueWindow_BOTTOM_SECTION_HEIGHT = 500;
			//Font 08 = 30 | Font 10 = 32
			constexpr auto DialogDialogueWindow_TEXT_COUNTER_WIDTH = 32;

	//DialogScriptEditorWindow.cpp Font Dependant Settings
		//Font Size
			//Font 08 = 20 | Font 10 = 22
			constexpr auto DialogScriptEditorWindow_FONT_SIZE = 22;

}
