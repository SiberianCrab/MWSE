#pragma once

namespace se::windows {
	bool isKeyDown(int key);

	inline bool isControlDown() {
		return isKeyDown(VK_CONTROL);
	}

	inline bool isLeftMouseDown() {
		return isKeyDown(VK_LBUTTON);
	}

	inline bool isRightMouseDown() {
		return isKeyDown(VK_RBUTTON);
	}

	std::filesystem::path getModulePath(HINSTANCE hInstance);
}
