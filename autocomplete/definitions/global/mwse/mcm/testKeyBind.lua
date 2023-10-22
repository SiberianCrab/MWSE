return {
	type = "function",
	description = [[This function check whether a certain key combination is currently pressed. It will only check ctrl, shift and alt modifier keys, matching the KeyBinder. It doesn't check mouse.]],
	arguments = {
		{ name = "keybind", type = "mwseKeyCombo" },
	},
	returns = { name = "pressed", type = "boolean" }
}