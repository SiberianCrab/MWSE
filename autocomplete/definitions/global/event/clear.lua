return {
	type = "function",
	description = [[Removes all callbacks registered for a given event.]],
	arguments = {
		{ name = "eventId", type = "string|tes3.event", optional = true },
		{ name = "filter",  type = "userdata|string|number", optional = true },
	},
}