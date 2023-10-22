return {
	type = "function",
	description = [[This function returns the distant fog settings for given weather type. These can be found in the Distant Land Weather Settings in MGE XE.]],
	arguments = {
		{ name = "weather", type = "tes3.weather", description = "Maps to values in [`tes3.weather`](https://mwse.github.io/MWSE/references/weather-types/) table." },
	},
	returns = {
		{ name = "result", type = "mgeDistantFogTable" }
	}
}
