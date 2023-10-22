return {
	type = "method",
	description = [[Removes an active body part and optionally sets override data that can be used prevent other items using the same location.]],
	arguments = {
		{ name = "layer", type = "tes3.activeBodyPartLayer", description = "A value from [`tes3.activeBodyPartLayer`](https://mwse.github.io/MWSE/references/active-body-part-layers/) namespace." },
		{ name = "index", type = "tes3.activeBodyPart", description = "A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace." },
		{ name = "setOverride", type = "boolean", optional = true, default = true, description = "A flag which controls whether the override data should be written." },
		{ name = "overrideData", type = "number", optional = true, default = "0", description = "Use -1 to prevent other items from appearing in the same location." },
	},
}
