return {
	type = "event",
	description = "The mouseWheel event fires when the mouse wheel is used, providing a delta value.",
	eventData = {
		["delta"] = {
			type = "number",
			readOnly = true,
			description = "The direction and strength of the mouse wheel movement. The value is positive for scrolling up, negative otherwise. This magnitude is hardware dependent.",
		},
		["isControlDown"] = {
			type = "number",
			readOnly = true,
			description = "True if control is held.",
		},
		["isShiftDown"] = {
			type = "number",
			readOnly = true,
			description = "True if either shift key is held.",
		},
		["isAltDown"] = {
			type = "number",
			readOnly = true,
			description = "True if alt is held.",
		},
		["isSuperDown"] = {
			type = "number",
			readOnly = true,
			description = "True if super (Windows key) is held.",
		},
	},
	examples = {
		["..\\..\\..\\global\\tes3\\isKeyEqual\\filtering"] = {
			title = "Filtering out key presses that aren't equal to the bound key combination"
		},
	},
}