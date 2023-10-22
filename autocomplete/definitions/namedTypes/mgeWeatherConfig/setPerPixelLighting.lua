return {
	type = "function",
	description = [[Sets the PPL values for a weather in MGE. The result table of `getPerPixelLighting` can be modified then passed to this function.]],
	arguments = {{
		name = "params",
		-- The type is set to union so we can pass the result table from
		-- the getPerPixelLighting here without the type checker complaining
		type = "table|mgePerPixelLightingTable",
		tableParams = {
			{ name = "weather", type = "tes3.weather", description = "Maps to values in [`tes3.weather`](https://mwse.github.io/MWSE/references/weather-types/) table." },
			{ name = "sun", type = "number", description = [[Corresponds to the value of "Sun brightness multiplier" setting for given weather in the Per-pixel Lighting Settings menu of MGE XE.]] },
			{ name = "ambient", type = "number", description = [[Corresponds to the value of "Ambient brightness multiplier" setting for given weather in the Per-pixel Lighting Settings menu of MGE XE.]] },
		},
	}},
}
