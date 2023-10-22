return {
	type = "function",
	description = [[This is used to change the distant fog settings for given weather type.]],
	arguments = {{
		name = "params",
		-- The type is set to union so we can pass the result table from
		-- the getDistantFog here without the type checker complaining
		type = "table|mgeDistantFogTable",
		tableParams = {
			{ name = "weather", type = "tes3.weather", description = "Maps to values in [`tes3.weather`](https://mwse.github.io/MWSE/references/weather-types/) table." },
			{ name = "distance", type = "number", description = [[Corresponds to the value of "Fog range factor" setting for given weather in the Distant Land Weather Settings of MGE XE.]] },
			{ name = "offset", type = "number", description = [[Corresponds to the value of "Fog offset" setting for given weather in the Distant Land Weather Settings of MGE XE.]] },
		},
	}},
}
