return {
	type = "function",
	description = [[Gets the input configuration for a given keybind.]],
	arguments = {
		{ name = "keybind", type = "tes3.keybind", description = "Maps to [`tes3.keybind`](https://mwse.github.io/MWSE/references/keybinds/) constants." }
	},
	returns = { name = "inputConfig", type = "tes3inputConfig" },
}