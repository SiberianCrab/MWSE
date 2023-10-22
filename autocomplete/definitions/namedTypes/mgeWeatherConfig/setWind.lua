return {
	type = "function",
	description = [[Sets the wind speed for a weather in MGE. The result table of `getWind` can be modified then passed to this function.]],
	arguments = {{
		name = "params",
		-- The type is set to union so we can pass the result table from
		-- the getWind here without the type checker complaining
		type = "table|mgeWindTable",
		tableParams = {
			{ name = "weather", type = "tes3.weather", description = "Maps to values in [`tes3.weather`](https://mwse.github.io/MWSE/references/weather-types/) table." },
			{ name = "speed", type = "number" },
		},
	}},
}
