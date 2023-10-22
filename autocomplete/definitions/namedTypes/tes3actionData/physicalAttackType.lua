return {
	type = "value",
	valuetype = "tes3.physicalAttackType",
	description = [[A number from the [`tes3.physicalAttackType`](https://mwse.github.io/MWSE/references/physical-attack-types/) enumeration identifying the physical attack type. Can be `tes3.physicalAttackType.slash`, `.chop`, `.thrust`, `.projectile`, `.creature1`, `.creature2`, or `.creature3.`

Proper time to change the attack direction is the [attackStart](https://mwse.github.io/MWSE/events/attackStart/) event. See the example below to see how.]],
	examples = {
		["..\\..\\..\\events\\standard\\attackStart\\directionChange"] = {
			title = "Changing axe attack direction"
		}
	}
}