return {
	type = "function",
	description = [[Gets the wind speed for a weather from MGE. This is returned in a table with the `speed` key, as well as the `weather` redefined. The result table can be modified, then sent back to `setWind`.]],
	arguments = {
		{ name = "weather", type = "tes3.weather", description = "Maps to values in [`tes3.weather`](https://mwse.github.io/MWSE/references/weather-types/) table." },
	},
	returns = {
		{ name = "result", type = "mgeWindTable", description = "A package containing the speed property." }
	},
}
