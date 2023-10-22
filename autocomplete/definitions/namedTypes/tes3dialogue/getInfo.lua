return {
	type = "method",
	description = [[Fetches the info that a given actor would produce for the dialogue.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "actor", type = "tes3mobileActor|tes3reference|string" },
			{ name = "context", type = "tes3.dialogueFilterContext", default = "tes3.dialogueFilterContext.script", description = "An override for how this info request should be treated. Maps to values in the [`tes3.dialogueFilterContext`](https://mwse.github.io/MWSE/references/dialogue-filter-context/) table." },
		}
	}},
	valuetype = "tes3dialogueInfo",
}
