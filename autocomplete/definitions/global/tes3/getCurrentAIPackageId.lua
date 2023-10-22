return {
	type = "function",
	description = [[Returns an actor's current AI package ID, just as the mwscript function `GetCurrentAIPackage` would.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "reference", type = "tes3mobileActor|tes3reference|string" },
		},
	}},
	returns = { name = "packageID", type = "tes3.aiPackage", description = "Maps to values in [`tes3.aiPackage`](https://mwse.github.io/MWSE/references/ai-packages/) table." }
}