return {
	type = "method",
	description = [[Performs a test for a given keybind, and optionally a transition state.]],
	arguments = {
		{ name = "key", type = "tes3.keybind", description = "The keybind to test. Constants available through [`tes3.keybind`](https://mwse.github.io/MWSE/references/keybinds/)." },
		{ name = "transition", type = "tes3.keyTransition", optional = true, description = "Transition state, e.g. down, or up. Constants available through [`tes3.keyTransition`](https://mwse.github.io/MWSE/references/key-transitions/)." },
	},
	valuetype = "boolean",
}