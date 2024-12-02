return {
	type = "function",
	description = [[Equips an item, optionally adding the item if needed. If the best match is already equipped, it does not perform an unequip-equip cycle, but does return `true`. If the item cannot be equipped, it will return `false`.

Equip may fail for the following reasons:

- The item cannot be found in the inventory.
- The exact match cannot be found when itemData is provided.
- When a weapon is being used to attack, it cannot be replaced during the attack animation.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "reference", type = "tes3reference|tes3mobileActor|string", description = "The reference to perform the equip on." },
			{ name = "item", type = "tes3item|string", description = "The item to equip." },
			{ name = "itemData", type = "tes3itemData", optional = true, description = "The item data of the specific item to equip, if a specific item is required." },
			{ name = "addItem", type = "boolean", optional = true, default = false, description = "If `true`, the item will be added to the actor's inventory if it is not already present." },
			{ name = "selectBestCondition", type = "boolean", optional = true, default = false, description = "If `true`, the item in the inventory with the best condition and best charge will be selected." },
			{ name = "selectWorstCondition", type = "boolean", optional = true, default = false, description = "If `true`, the item in the inventory with the worst condition and worst charge will be selected. Can be useful for selecting tools." },
			{ name = "bypassEquipEvents", type = "boolean", optional = true, default = false, description = "If `true`, this call will not raise any `equip`-related events." },
		},
	}},
	returns = "itemEquipped",
	valuetype = "boolean",
}
