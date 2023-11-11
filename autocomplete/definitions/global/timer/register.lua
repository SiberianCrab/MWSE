return {
	type = "function",
	description = [[Registers a named timer with a callback to persist between game sessions. Bear in mind that nothing in MWSE is sandboxed, so all the registered timers are in the global namespace. Consider prefixing your timer with mod name or something else to avoid name collisions. For instance, `iceCreamMod:myTimer`.

!!! tip
	It's recommended to study the [Object Lifetimes](../guides/object-lifetimes.md) guide. It describes how to safely use [tes3reference](../types/tes3reference.md) objects inside timer callbacks.]],
	arguments = {
		{ name = "name", type = "string", description = "Name of the registered timer." },
		{ name = "fn", type = "fun(e: mwseTimerCallbackData)", description = "A callback function for the timer." },
	},
	examples = {
		["dayLater"] = {
			title = "Persistent timers tutorial with `.data` usage",
			description = "The timer registered in the example is registered and persistent. That renders starting the timer on every loaded event unnecessary. Its state is saved, and it continues where it stopped after loading a save.",
		},
	},
}
