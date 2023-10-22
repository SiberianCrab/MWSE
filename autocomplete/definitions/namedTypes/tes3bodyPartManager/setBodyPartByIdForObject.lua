return {
	type = "method",
	description = [[The method sets a new body part for a given object.]],
	arguments = {
		{ name = "item", type = "tes3item", description = "The item that the body part is from." },
		{ name = "index", type = "tes3.activeBodyPart", description = "A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace." },
		{ name = "bodyPartId", type = "string", description = "The unique ID of the `tes3bodyPart` object to set as a new body part for given object." },
		{ name = "isFirstPerson", type = "boolean", optional = true, default = "false", description = "A flag which must be set if the target reference is the first person player." },
	},
}
