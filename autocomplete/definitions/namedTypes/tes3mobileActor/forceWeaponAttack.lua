return {
	type = "method",
	description = [[Causes the actor to perform a weapon swing immediately towards its current target. For the player, it will swing and release immediately (minimum damage), and also may hit any target in range.

The actor must be in combat, with its weapon or hands readied, to be able to swing its weapon. This function does not interrupt existing attacks, casting, or any other actions. It returns true if it was able to start the weapon swing.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "attackType", type = "tes3.physicalAttackType", optional = true, description = "The physical attack type to use for melee weapons (slash, chop, thrust). Maps to values in [`tes3.physicalAttackType`](https://mwse.github.io/MWSE/references/physical-attack-types/) namespace. When not specified, it uses a weighted random attack type for NPCs and creatures." },
			{ name = "swing", type = "number", optional = true, description = "The strength of the attack swing, in the range [0 to 1]. When not specified, the attack swing is randomized. This value cannot affect the player swing, as player attacks are driven by input." },
		},
	}},
	valuetype = "boolean",
}