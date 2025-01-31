return {
	type = "method",
	description = [[Creates a clickable button, whose text changes linearly through options as it is clicked. Register the `valueChanged` event for when the option is cycled or changed via script.

Button specific properties can be accessed through the `widget` property. The widget type for buttons is [`tes3uiCycleButton`](https://mwse.github.io/MWSE/types/tes3uiCycleButton/).]],
	arguments = { {
		name = "params",
		type = "table",
		tableParams = {
			{ name = "id", type = "string|number", description = "An identifier to help find this element later.", optional = true },
		},
	} },
	valuetype = "tes3uiElement",
}
