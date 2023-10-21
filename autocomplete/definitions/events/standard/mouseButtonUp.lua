return {
	type = "event",
	description = "This event fires when a button on the mouse is released.",
	related = { "mouseButtonDown" },
	eventData = {
		["button"] = {
			type = "integer",
			readOnly = true,
			description = "The button index that was released.",
		},
		["isControlDown"] = {
			type = "boolean",
			readOnly = true,
			description = "True if control is held.",
		},
		["isShiftDown"] = {
			type = "boolean",
			readOnly = true,
			description = "True if either shift key is held.",
		},
		["isAltDown"] = {
			type = "boolean",
			readOnly = true,
			description = "True if alt is held.",
		},
		["isSuperDown"] = {
			type = "boolean",
			readOnly = true,
			description = "True if super (Windows key) is held.",
		},
	},
	filter = "button",
}