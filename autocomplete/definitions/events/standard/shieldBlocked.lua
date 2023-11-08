return {
	type = "event",
	description = "This event is fired when a melee strike is blocked, and the equipped shield is about to take damage from the strike. It allows modification of the damage applied to the shield.",
	eventData = {
		["conditionDamage"] = {
			type = "number",
			description = "The shield's condition will be reduced by this amount. It is initially equal to the pre-armor-mitigation damage value of the strike.",
		},
		["attacker"] = {
			type = "tes3mobileActor",
			readOnly = true,
			description = "The mobile actor dealing the damage.",
		},
		["mobile"] = {
			type = "tes3mobileActor",
			readOnly = true,
			description = "The mobile actor which is blocking the strike.",
		},
		["reference"] = {
			type = "tes3reference",
			readOnly = true,
			description = "A shortcut to the mobile's reference.",
		},
	},
	filter = "reference",
	blockable = false,
}