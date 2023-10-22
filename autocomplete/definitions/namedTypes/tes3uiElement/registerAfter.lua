return {
	type = "method",
	description = [[Sets an `event` handler to run after any existing event handler on the element. Can be any event usable with `register`. The callback receives an argument with the event data. See `register` for details.]],
	arguments = {
		{ name = "eventID", type = "tes3.uiEvent", description = "The event id. Maps to values in [`tes3.uiEvent`](https://mwse.github.io/MWSE/references/ui-events/)." },
		{ name = "callback", type = "fun(e: tes3uiEventData): boolean?", description = "The callback function." },
	},
}