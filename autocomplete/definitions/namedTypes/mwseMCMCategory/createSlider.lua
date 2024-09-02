return {
	type = "method",
	description = [[Creates a new nested Slider.]],
	arguments = {{
		name = "data",
		type = "table",
		tableParams = {
			{ name = "label", type = "string", optional = true, description = "Text shown above the slider. If left as a normal string, it will be shown in the form: [`label`]: [`self.variable.value`]. If the string contains a '%s' format operator, the value will be formatted into it." },
			{ name = "variable", type = "mwseMCMVariable|mwseMCMSettingNewVariable", optional = true,
				description = "A variable for this setting. If not provided, this setting will try to create a variable using the `config` and `configKey` parameters, if possible."
			},
			{ name = "config", type = "table", optional = true, default = "`parentComponent.config`",
				description = "The config to use when creating a [`mwseMCMTableVariable`](./mwseMCMTableVariable.md) for this `Setting`. \z
						If provided, it will override the config stored in `parentComponent`. \z
						Otherwise, the value in `parentComponent` will be used."
			},
			{ name = "defaultConfig", type = "table", optional = true, default = "`parentComponent.defaultConfig`",
				description = "The `defaultConfig` to use when creating a [`mwseMCMTableVariable`](./mwseMCMTableVariable.md) for this `Setting`. \z
					If provided, it will override the `defaultConfig` stored in `parentComponent`. \z
					Otherwise, the value in `parentComponent` will be used."
			},
			{ name = "configKey", type = "string|number", optional = true,
				description = "The `configKey` used to create a new [`mwseMCMTableVariable`](./mwseMCMTableVariable.md). \z
					If this is provided, along with a `config` (which may be inherited from the `parentComponent`), then a new \z
						[`mwseMCMTableVariable`](./mwseMCMTableVariable.md) variable will be created for this setting."
			},
			{ name = "converter", type = "fun(newValue: unknown): unknown", optional = true,
				description = "A converter to use for this component's `variable`."
			},
			{ name = "defaultSetting", type = "unknown", optional = true,
				description = "If `defaultSetting` wasn't passed in the `variable` table, can be passed here. \z
					The new variable will be initialized to this value. If not provided, then the value in `defaultConfig` will be used, if possible."
			},
			{ name = "showDefaultSetting", type = "boolean", optional = true, default = "`parentComponent.showDefaultSetting`",
				description = "If `true`, and in a [Sidebar Page](../types/mwseMCMSideBarPage.md), then the `defaultSetting` of this setting's `variable` will be shown below its `description`. \z
					The `defaultSetting` will be formatted in accordance with the `convertToLabelValue` function. \z
					**Note:** This parameter does not update the `description` field.",
			},
			{ name = "min", type = "number", optional = true, default = 0, description = "Minimum value of slider." },
			{ name = "max", type = "number", optional = true, default = 100, description = "Maximum value of slider." },
			{ name = "step", type = "number", optional = true, default = 1, description = "How far the slider moves when you press the arrows." },
			{ name = "jump", type = "number", optional = true, default = 5, description = "How far the slider jumps when you click an area inside the slider." },
			{ name = "decimalPlaces", type = "integer", optional = true, default = 0, description = "The number of decimal places of precision. Must be a nonnegative integer." },
			{ name = "description", type = "string", optional = true, description = "If in a [Sidebar Page](../types/mwseMCMSideBarPage.md), the description will be shown on mouseover." },
			{ name = "callback", type = "fun(self: mwseMCMSlider)", optional = true, description = "The custom function called when the player interacts with this Setting." },
			{ name = "inGameOnly", type = "boolean", optional = true, default = false, description = "If true, the setting is disabled while the game is on main menu." },
			{ name = "restartRequired", type = "boolean", optional = true, default = false, description = "If true, updating this Setting will notify the player to restart the game." },
			{ name = "restartRequiredMessage", type = "string", optional = true, description = 'The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect."' },
			{ name = "indent", type = "integer", optional = true, default = 12, description = "The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component." },
			{ name = "childIndent", type = "integer", optional = true, description = "The left padding size in pixels. Used on all the child components." },
			{ name = "paddingBottom", type = "integer", optional = true, default = 4, description = "The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component." },
			{ name = "childSpacing", type = "integer", optional = true, description = "The bottom border size in pixels. Used on all the child components." },
			{ name = "convertToLabelValue", type = "fun(self: mwseMCMSlider, variableValue: number): number|string", optional = true, description = "Define a custom formatting function for displaying variable values." },
			{ name = "postCreate", type = "fun(self: mwseMCMSlider)", optional = true, description = "Can define a custom formatting function to make adjustments to any element saved in `self.elements`." },
		}
	}},
	returns = {{
		name = "slider", type = "mwseMCMSlider"
	}},
	examples = {
		["DecimalSlider"] = {
			title = "DecimalSlider",
			description = "The following example shows how to create a slider that keeps the variable value a floating point number with precision of 2 decimal places."
		},
		["..\\..\\mwseMCMSlider\\convertToLabelValue\\DistanceSlider"] = {
			title = "DistanceSlider",
			description = "The following example shows how the `convertToLabelValue` parameter can be used to create a slider for a config setting that handles distances. \z
				The config setting will be stored using game units, but the displayed value will be in real-world units. Recall that 1 game unit corresponds to 22.1 feet, and 1 foot is 0.3048 meters."
		},
		["..\\..\\mwseMCMSlider\\convertToLabelValue\\SkillSlider"] = {
			title = "SkillSlider",
			description = "Here is an (admittedly less practical) example to help highlight the different ways `convertToLabelValue` can be used. \z
				In this example, it will be used to create a slider that stores a `tes3.skill` constant in the config, and then displays the name of the corresponding skill."
		},
	},

}
