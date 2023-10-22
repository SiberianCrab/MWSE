return {
	type = "function",
	description = [[Fetches the core game object for a given skill ID.]],
	arguments = {
		{ name = "id", type = "tes3.skill", description = "Maps to [`tes3.skill`](https://mwse.github.io/MWSE/references/skills/) enumeration." }
	},
	returns = {{ name = "skill", type = "tes3skill" }},
}