return {
	type = "function",
	description = [[Causes a target actor to play a voiceover. To stop a currently playing voiceover see `tes3.removeSound()`.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "actor", type = "tes3mobileActor|tes3reference|string", description = "The actor to play a voiceover." },
			{ name = "voiceover", type = "tes3.voiceover|integer|string", description = "Maps to [`tes3.voiceover`](https://mwse.github.io/MWSE/references/voiceovers/) constants." },
		},
	}},
	returns = { name = "played", type = "boolean" },
}