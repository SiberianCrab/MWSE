return {
	type = "function",
	description = [[Gets the PPL data for a weather from MGE. These are returned in a table with the `sun` and `ambient` keys, as well as the `weather` redefined. The result table can be modified, then sent back to `setPerPixelLighting`.]],
	arguments = {
		{ name = "weather", type = "tes3.weather", description = "Maps to values in [`tes3.weather`](https://mwse.github.io/MWSE/references/weather-types/) table." },
	},
	returns = {
		{ name = "result", type = "mgePerPixelLightingTable" }
	},
}
