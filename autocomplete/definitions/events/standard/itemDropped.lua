return {
	type = "event",
	description = "This event fires when an item is dropped.",
	eventData = {
		["reference"] = {
			type = "tes3reference",
			readOnly = true,
			description = "The reference to the dropped item.",
		},
	},
	filter = "reference.baseObject",
}