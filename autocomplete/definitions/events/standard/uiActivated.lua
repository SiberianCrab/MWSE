return {
	type = "event",
	description = [[This event is invoked after a UI menu has been built or made visible, at the point that all menu elements contain updated data. Below is a table with all the menus this event triggers for.

Menu id                 | Description
----------------------- | -------------------------
`"MenuAlchemy"`         |
`"MenuAttributes"`      |
`"MenuAttributesList"`  | Enchanting/spellmaking effect attribute
`"MenuAudio"`           | Options, audio
`"MenuBarter"`          |
`"MenuBirthSign"`       |
`"MenuBook"`            |
`"MenuChooseClass"`     |
`"MenuClassChoice"`     |
`"MenuClassMessage"`    |
`"MenuConsole"`         |
`"MenuContents"`        | Container/NPC inventory
`"MenuCreateClass"`     |
`"MenuCtrls"`           | Options, controls
`"MenuDialog"`          |
`"MenuEnchantment"`     |
`"MenuInput"`           |
`"MenuInputSave"`       |
`"MenuInventory"`       | Player inventory
`"MenuInventorySelect"` | Item selector
`"MenuJournal"`         |
`"MenuLevelUp"`         |
`"MenuLoad"`            |
`"MenuLoading"`         |
`"MenuMagic"`           | Spell/enchanted item selector
`"MenuMagicSelect"`     |
`"MenuMap"`             |
`"MenuMapNoteEdit"`     |
`"MenuMessage"`         |
`"MenuMulti"`           | Status bars, current weapon/magic, active effects and minimap
`"MenuName"`            |
`"MenuNotify1"`         |
`"MenuNotify2"`         |
`"MenuNotify3"`         |
`"MenuOptions"`         | Main menu
`"MenuPersuasion"`      |
`"MenuPrefs"`           | Options, preferences
`"MenuQuantity"`        |
`"MenuQuick"`           | Quick keys
`"MenuRaceSex"`         |
`"MenuRepair"`          |
`"MenuRestWait"`        |
`"MenuSave"`            |
`"MenuScroll"`          |
`"MenuServiceRepair"`   |
`"MenuServiceSpells"`   |
`"MenuServiceTraining"` |
`"MenuServiceTravel"`   |
`"MenuSetValues"`       | Enchanting/spellmaking effect values
`"MenuSkills"`          |
`"MenuSkillsList"`      | Enchanting/spellmaking effect skill
`"MenuSpecialization"`  |
`"MenuSpellmaking"`     |
`"MenuStat"`            | Player attributes, skills, factions etc.
`"MenuStatReview"`      |
`"MenuSwimFillBar"`     |
`"MenuTimePass"`        |
`"MenuTopic"`           |
`"MenuVideo"`           | Options, video
]],
	eventData = {
		["element"] = {
			type = "tes3uiElement",
			readOnly = true,
			description = "The menu element that was created. The event is filtered on element.name.",
		},
		["newlyCreated"] = {
			type = "boolean",
			readOnly = true,
			description = "`true` if the menu was created for the first time or destroyed and re-created; `false` if it was made visible after being hidden. This can be used when adding custom elements to a menu, as elements previously added will still exist if the menu was hidden. If the menu was re-created, the elements will need to be added again.",
		},
	},
	filter = "element.name",
}