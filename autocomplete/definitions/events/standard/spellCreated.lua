return{
	type = "event",
	description = "This event is triggered when a new spell is created using spellmaking services or by a script using `tes3.createObject()`.",
	eventData = {
		["spell"] = {
			type = "tes3spell",
			description = "A spell which was created.",
		},
		["source"] = {
			type = "tes3.spellSource",
			description = "Was the origin of the spell spellmaker or a script?  Maps to values in [`tes3.spellSource`](https://mwse.github.io/MWSE/references/spell-sources/) namespace.",
		},
	},
	filter = "source",
}
