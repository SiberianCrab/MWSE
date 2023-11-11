return {
	type = "function",
	description = [[Creates a timer that will finish the next frame.

!!! tip
	It's recommended to study the [Object Lifetimes](../guides/object-lifetimes.md) guide. It describes how to safely use [tes3reference](../types/tes3reference.md) objects inside timer callbacks.]],
	arguments = {
		{ name = "callback", type = "fun(e: mwseTimerCallbackData)", description = "The callback function that will execute when the timer expires." },
	},
	returns = { name = "timer", type = "mwseTimer" },
}
