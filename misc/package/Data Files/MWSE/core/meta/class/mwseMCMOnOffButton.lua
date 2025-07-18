--- @meta

-- This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
-- More information: https://github.com/MWSE/MWSE/tree/master/docs

--- Toggles a Variable between true and false, with the `buttonText` switching between the strings "On" and "Off".
--- @class mwseMCMOnOffButton : mwseMCMButton, mwseMCMSetting, mwseMCMComponent
--- @field variable mwseMCMConfigVariable|mwseMCMCustomVariable|mwseMCMGlobal|mwseMCMGlobalBoolean|mwseMCMPlayerData|mwseMCMTableVariable|mwseMCMVariable The Variable this button will update.
mwseMCMOnOffButton = {}

--- Creates a new OnOffButton.
--- @param data? mwseMCMOnOffButton.new.data This table accepts the following values:
--- 
--- `label?`: string — *Optional*. Text shown next to the button.
--- 
--- `description?`: string — *Optional*. If in a [Sidebar Page](../types/mwseMCMSideBarPage.md), the description will be shown on mouseover.
--- 
--- `leftSide?`: boolean — *Default*: `true`. If true, the button will be created on the left and label on the right.
--- 
--- `variable?`: mwseMCMConfigVariable|mwseMCMCustomVariable|mwseMCMGlobal|mwseMCMGlobalBoolean|mwseMCMPlayerData|mwseMCMTableVariable|mwseMCMVariable|mwseMCMSettingNewVariable — *Optional*. A variable of given class for this Button.
--- 
--- `defaultSetting?`: boolean — *Default*: `false`. If `defaultSetting` wasn't passed in the `variable` table, can be passed here. The new variable will be initialized to this value.
--- 
--- `callback?`: fun(self: mwseMCMOnOffButton) — *Optional*. The custom function called when the player interacts with this Button.
--- 
--- `inGameOnly?`: boolean — *Default*: `false`. If true, the setting is disabled while the game is on main menu.
--- 
--- `restartRequired?`: boolean — *Default*: `false`. If true, updating this Setting will notify the player to restart the game.
--- 
--- `restartRequiredMessage?`: string — *Optional*. The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect."
--- 
--- `indent?`: integer — *Default*: `12`. The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component.
--- 
--- `childIndent?`: integer — *Optional*. The left padding size in pixels. Used on all the child components.
--- 
--- `paddingBottom?`: integer — *Default*: `4`. The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component.
--- 
--- `childSpacing?`: integer — *Optional*. The bottom border size in pixels. Used on all the child components.
--- 
--- `postCreate?`: fun(self: mwseMCMOnOffButton) — *Optional*. Can define a custom formatting function to make adjustments to any element saved in `self.elements`.
--- 
--- `class?`: string — *Optional*. No description yet available.
--- 
--- `componentType?`: string — *Optional*. No description yet available.
--- 
--- `parentComponent?`: mwseMCMActiveInfo|mwseMCMBinder|mwseMCMButton|mwseMCMCategory|mwseMCMColorPicker|mwseMCMColorPickerButton|mwseMCMComponent|mwseMCMCycleButton|mwseMCMDropdown|mwseMCMExclusionsPage|mwseMCMFilterPage|mwseMCMHyperlink|mwseMCMInfo|mwseMCMKeyBinder|mwseMCMLogLevelOptions|mwseMCMMouseBinder|mwseMCMMouseOverInfo|mwseMCMMouseOverPage|mwseMCMOnOffButton|mwseMCMPage|mwseMCMParagraphField|mwseMCMPercentageSlider|mwseMCMSetting|mwseMCMSideBarPage|mwseMCMSideBySideBlock|mwseMCMSlider|mwseMCMTemplate|mwseMCMTextField|mwseMCMYesNoButton — *Optional*. No description yet available.
--- @return mwseMCMOnOffButton button No description yet available.
function mwseMCMOnOffButton:new(data) end

---Table parameter definitions for `mwseMCMOnOffButton.new`.
--- @class mwseMCMOnOffButton.new.data
--- @field label? string *Optional*. Text shown next to the button.
--- @field description? string *Optional*. If in a [Sidebar Page](../types/mwseMCMSideBarPage.md), the description will be shown on mouseover.
--- @field leftSide? boolean *Default*: `true`. If true, the button will be created on the left and label on the right.
--- @field variable? mwseMCMConfigVariable|mwseMCMCustomVariable|mwseMCMGlobal|mwseMCMGlobalBoolean|mwseMCMPlayerData|mwseMCMTableVariable|mwseMCMVariable|mwseMCMSettingNewVariable *Optional*. A variable of given class for this Button.
--- @field defaultSetting? boolean *Default*: `false`. If `defaultSetting` wasn't passed in the `variable` table, can be passed here. The new variable will be initialized to this value.
--- @field callback? fun(self: mwseMCMOnOffButton) *Optional*. The custom function called when the player interacts with this Button.
--- @field inGameOnly? boolean *Default*: `false`. If true, the setting is disabled while the game is on main menu.
--- @field restartRequired? boolean *Default*: `false`. If true, updating this Setting will notify the player to restart the game.
--- @field restartRequiredMessage? string *Optional*. The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect."
--- @field indent? integer *Default*: `12`. The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component.
--- @field childIndent? integer *Optional*. The left padding size in pixels. Used on all the child components.
--- @field paddingBottom? integer *Default*: `4`. The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component.
--- @field childSpacing? integer *Optional*. The bottom border size in pixels. Used on all the child components.
--- @field postCreate? fun(self: mwseMCMOnOffButton) *Optional*. Can define a custom formatting function to make adjustments to any element saved in `self.elements`.
--- @field class? string *Optional*. No description yet available.
--- @field componentType? string *Optional*. No description yet available.
--- @field parentComponent? mwseMCMActiveInfo|mwseMCMBinder|mwseMCMButton|mwseMCMCategory|mwseMCMColorPicker|mwseMCMColorPickerButton|mwseMCMComponent|mwseMCMCycleButton|mwseMCMDropdown|mwseMCMExclusionsPage|mwseMCMFilterPage|mwseMCMHyperlink|mwseMCMInfo|mwseMCMKeyBinder|mwseMCMLogLevelOptions|mwseMCMMouseBinder|mwseMCMMouseOverInfo|mwseMCMMouseOverPage|mwseMCMOnOffButton|mwseMCMPage|mwseMCMParagraphField|mwseMCMPercentageSlider|mwseMCMSetting|mwseMCMSideBarPage|mwseMCMSideBySideBlock|mwseMCMSlider|mwseMCMTemplate|mwseMCMTextField|mwseMCMYesNoButton *Optional*. No description yet available.

--- Toggles the variable value. Updates the button's text and calls the `update` method.
function mwseMCMOnOffButton:press() end

