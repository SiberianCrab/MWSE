return {
	type = "function",
	description = [[This function fetches a reference's attached animation groups. The animation groups match the values from [`tes3.animationGroup`](https://mwse.github.io/MWSE/references/animation-groups/) table.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "reference", type = "tes3reference", description = "A reference whose animation groups to fetch." },
		},
	}},
	returns = {
		{ name = "lowerBodyGroup", type = "tes3.animationGroup" },
		{ name = "upperBodyGroup", type = "tes3.animationGroup" },
		{ name = "leftArmGroup", type = "tes3.animationGroup" },
	},
	examples = {
		["usage"] = {
			title = "Getting animation timings for bow animations",
		}
	}
}
