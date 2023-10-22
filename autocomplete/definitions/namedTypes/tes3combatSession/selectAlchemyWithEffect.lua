return {
	type = "method",
	description = "Selects the alchemy item with the greatest value, for a given effect ID and loads it into the `selectedItem` property.",
	arguments = {
		{ name = "id", type = "tes3.effect", description = "Maps to values in [`tes3.effect`](https://mwse.github.io/MWSE/references/magic-effects/) table." },
	},
	returns = {
		{ name = "result", type = "number" },
	}
}