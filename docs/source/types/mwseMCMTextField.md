# mwseMCMTextField
<div class="search_terms" style="display: none">mwsemcmtextfield</div>

<!---
	This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
	More information: https://github.com/MWSE/MWSE/tree/master/docs
-->

A TextField allows you to enter a single line of text and submit with a button. You can also force it to only accept numbers with the `numbersOnly` field.

This type inherits the following: [mwseMCMSetting](../types/mwseMCMSetting.md), [mwseMCMComponent](../types/mwseMCMComponent.md).
## Properties

### `buttonText`
<div class="search_terms" style="display: none">buttontext</div>

The text shown on the button next to the input field. The default text is a localized version of: "Submit".

**Returns**:

* `result` (string)

***

### `callback`
<div class="search_terms" style="display: none">callback</div>

The custom function called when the player interacts with this Setting.

**Returns**:

* `result` (nil, fun(self: [mwseMCMSetting](../types/mwseMCMSetting.md)))

***

### `childIndent`
<div class="search_terms" style="display: none">childindent</div>

The left padding size in pixels. Used on all the child components.

**Returns**:

* `result` (integer, nil)

***

### `childSpacing`
<div class="search_terms" style="display: none">childspacing</div>

The bottom border size in pixels. Used on all the child components.

**Returns**:

* `result` (integer, nil)

***

### `class`
<div class="search_terms" style="display: none">class</div>

Every MCM component has a unique string indentifier specific to that component. These strings are the filename of the file implementing a component. These are found in `core\\mcm\\components`.

**Returns**:

* `result` (string)

***

### `componentType`
<div class="search_terms" style="display: none">componenttype</div>

The type of this component.

**Returns**:

* `result` ("Setting")

***

### `config`
<div class="search_terms" style="display: none">config</div>

The config to use when creating a [`mwseMCMTableVariable`](./mwseMCMTableVariable.md) for this `Setting`. If provided, it will override the config stored in `parentComponent`. Otherwise, the value in `parentComponent` will be used.

**Returns**:

* `result` (table, nil)

***

### `configKey`
<div class="search_terms" style="display: none">configkey</div>

The `configKey` used to create a new [`mwseMCMTableVariable`](./mwseMCMTableVariable.md). If this is provided, along with a `config` (which may be inherited from the `parentComponent`), then a new [`mwseMCMTableVariable`](./mwseMCMTableVariable.md) variable will be created for this setting.

**Returns**:

* `result` (string, number, nil)

***

### `converter`
<div class="search_terms" style="display: none">converter</div>

A converter to use for this component's `variable`.

**Returns**:

* `result` ((fun(newValue: unknown): unknown), nil)

***

### `createContentsContainer`
<div class="search_terms" style="display: none">createcontentscontainer, contentscontainer</div>

This method creates the contents of a component. Not every component implements this method.

**Returns**:

* `result` (nil, fun(self: [mwseMCMComponent](../types/mwseMCMComponent.md), outerContainer: [tes3uiElement](../types/tes3uiElement.md)))

***

### `defaultConfig`
<div class="search_terms" style="display: none">defaultconfig</div>

The `defaultConfig` to use when creating a [`mwseMCMTableVariable`](./mwseMCMTableVariable.md) for this `Setting`. If provided, it will override the `defaultConfig` stored in `parentComponent`. Otherwise, the value in `parentComponent` will be used.

**Returns**:

* `result` (table, nil)

***

### `defaultSetting`
<div class="search_terms" style="display: none">defaultsetting</div>

If `defaultSetting` wasn't passed in the `variable` table, can be passed here. The new variable will be initialized to this value. If not provided, then the value in `defaultConfig` will be used, if possible.

**Returns**:

* `result` (unknown, nil)

***

### `description`
<div class="search_terms" style="display: none">description</div>

If in a [Sidebar Page](./mwseMCMSideBarPage.md), the description will be shown on mouseover.

**Returns**:

* `result` (string, nil)

***

### `elements`
<div class="search_terms" style="display: none">elements</div>

This dictionary-style table holds all the UI elements of the TextField, for easy access.

**Returns**:

* `result` ([mwseMCMTextFieldElements](../types/mwseMCMTextFieldElements.md))

***

### `indent`
<div class="search_terms" style="display: none">indent</div>

The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component.

**Returns**:

* `result` (integer)

***

### `inGameOnly`
<div class="search_terms" style="display: none">ingameonly</div>

If true, the setting is disabled while the game is on main menu. If this is enabled, it will override the value of the `inGameOnly` parameter on this setting's `variable`.

**Returns**:

* `result` (boolean)

***

### `label`
<div class="search_terms" style="display: none">label</div>

Text shown above the text field.

**Returns**:

* `result` (string)

***

### `makeComponent`
<div class="search_terms" style="display: none">makecomponent</div>

This method must be implemented by child classes of mwseMCMSetting.

**Returns**:

* `result` (nil, fun(self: [mwseMCMSetting](../types/mwseMCMSetting.md), innerContainer: [tes3uiElement](../types/tes3uiElement.md)))

***

### `minHeight`
<div class="search_terms" style="display: none">minheight</div>

The minimum height set on the `self.elements.border` UI element.

**Returns**:

* `result` (integer, nil)

***

### `mouseOvers`
<div class="search_terms" style="display: none">mouseovers</div>

This array of UI elements will have an event handler registered to trigger "MCM:MouseOver" event. For more info, see [registerMouseOverElements](#registermouseoverelements) method.

**Returns**:

* `result` ([tes3uiElement](../types/tes3uiElement.md)[], nil)

***

### `numbersOnly`
<div class="search_terms" style="display: none">numbersonly</div>

If true, only numbers will be allowed in this TextField.

**Returns**:

* `result` (boolean)

***

### `paddingBottom`
<div class="search_terms" style="display: none">paddingbottom</div>

The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component.

**Returns**:

* `result` (integer)

***

### `parentComponent`
<div class="search_terms" style="display: none">parentcomponent</div>



**Returns**:

* `result` ([mwseMCMComponent](../types/mwseMCMComponent.md), nil)

***

### `postCreate`
<div class="search_terms" style="display: none">postcreate</div>

Custom formatting function to make adjustments to any element saved in `self.elements`.

**Returns**:

* `result` (nil, fun(self: [mwseMCMComponent](../types/mwseMCMComponent.md)))

***

### `restartRequired`
<div class="search_terms" style="display: none">restartrequired</div>

If true, updating this Setting will notify the player to restart the game.

**Returns**:

* `result` (boolean)

***

### `restartRequiredMessage`
<div class="search_terms" style="display: none">restartrequiredmessage</div>

The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect.".

**Returns**:

* `result` (string)

***

### `sCancel`
<div class="search_terms" style="display: none">scancel</div>

Set to the value of `sCancel` GMST.

**Returns**:

* `result` (string)

***

### `showDefaultSetting`
<div class="search_terms" style="display: none">showdefaultsetting, defaultsetting</div>

If true, then the `defaultSetting` of this setting's `variable` will be shown below its description.

**Returns**:

* `result` (boolean)

***

### `sNewValue`
<div class="search_terms" style="display: none">snewvalue</div>

The message shown after a new value is submitted. This can be formatted with a '%s' which will be replaced with the new value. The default text is a localized version of: "New value: '%s'".

**Returns**:

* `result` (string)

***

### `sNo`
<div class="search_terms" style="display: none">sno</div>

Set to the value of `sNo` GMST.

**Returns**:

* `result` (string)

***

### `sOff`
<div class="search_terms" style="display: none">soff</div>

Set to the value of `sOff` GMST.

**Returns**:

* `result` (string)

***

### `sOK`
<div class="search_terms" style="display: none">sok</div>

Set to the value of `sOK` GMST.

**Returns**:

* `result` (string)

***

### `sOn`
<div class="search_terms" style="display: none">son</div>

Set to the value of `sOn` GMST.

**Returns**:

* `result` (string)

***

### `sYes`
<div class="search_terms" style="display: none">syes</div>

Set to the value of `sYes` GMST.

**Returns**:

* `result` (string)

***

### `variable`
<div class="search_terms" style="display: none">variable</div>

The Variable this setting will update.

**Returns**:

* `result` ([mwseMCMVariable](../types/mwseMCMVariable.md), nil)

***

## Methods

### `callback`
<div class="search_terms" style="display: none">callback</div>

This method is called when setting is updated. Shows a messageBox with `self.sNewValue` with curent variable value formatted in.

```lua
myObject:callback()
```

***

### `checkDisabled`
<div class="search_terms" style="display: none">checkdisabled</div>

Returns true if the component should be disabled.

Componets with a variable:

- True if the Component's **variable** has `inGameOnly` field set to true, and the game is on the main menu. For components with multiple subcomponent ([Category](./mwseMCMCategory.md)), the check is done for each subcomponent.

Components without a variable:

- True if the **Component's** `inGameOnly` field is set to true, and the game is on the main menu.


```lua
local result = myObject:checkDisabled()
```

**Returns**:

* `result` (boolean)

***

### `convertToLabelValue`
<div class="search_terms" style="display: none">converttolabelvalue</div>

This function specifies how values stored in the `variable` field should correspond to values displayed by this setting.

```lua
local labelValue = myObject:convertToLabelValue(variableValue)
```

**Parameters**:

* `variableValue` (number)

**Returns**:

* `labelValue` (number, string)

***

### `create`
<div class="search_terms" style="display: none">create</div>

This method creates the UI elements that comprise this Setting.

```lua
myObject:create(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `createContentsContainer`
<div class="search_terms" style="display: none">createcontentscontainer, contentscontainer</div>

This method creates the UI elements specific to TextField.

```lua
myObject:createContentsContainer(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `createInnerContainer`
<div class="search_terms" style="display: none">createinnercontainer, innercontainer</div>

Creates component's innerContainer UI element inside given `parentBlock`, and stores it in the `self.elements.innerContainer`. The innerContainer will add `self.indent` additional padding on the left if the component has a label.

```lua
myObject:createInnerContainer(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `createLabel`
<div class="search_terms" style="display: none">createlabel, label</div>

Creates component's label UI element.

First, it calls `self:createLabelBlock` and creates the label element inside new `labelBlock`. Stores both new UI elements in the `self.elements` and `self.mouseOvers`.

```lua
myObject:createLabel(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `createLabelBlock`
<div class="search_terms" style="display: none">createlabelblock, labelblock</div>

Creates component's labelBlock UI element inside given `parentBlock`, and stores it in the `self.elements.labelBlock` and `self.mouseOvers`.

```lua
myObject:createLabelBlock(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `createOuterContainer`
<div class="search_terms" style="display: none">createoutercontainer, outercontainer</div>

Creates component's outerContainer UI element inside given `parentBlock`, and stores it in the `self.elements.outerContainer` and `self.mouseOvers`. The outerContainer holds all the other UI elements that comprise a component.

```lua
myObject:createOuterContainer(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `createSubmitButton`
<div class="search_terms" style="display: none">createsubmitbutton, submitbutton</div>

This method creates the submit button UI element and stores it in `self.elements.submitButton`.

```lua
myObject:createSubmitButton(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `disable`
<div class="search_terms" style="display: none">disable</div>

This method disables the component's UI elements. That includes: changing the color of the UI elements to the `tes3.palette.disabledColor` and setting button widget state to `tes3.uiState.disabled`.

```lua
myObject:disable()
```

***

### `enable`
<div class="search_terms" style="display: none">enable</div>

Enables the component's UI elements. That includes: changing the color of the UI elements to the `tes3.palette.normalColor` and registering handlers for `tes3.uiEvent.mouseClick` for buttons.

```lua
myObject:enable()
```

***

### `getMouseOverText`
<div class="search_terms" style="display: none">getmouseovertext, mouseovertext</div>

Retrieves the text that this setting should display in any related [`mouseOverInfo`s](./mwseMCMMouseOverInfo.md). This method currently utilized to display this component's description whenever the component is in a [`SideBarPage`](./mwseMCMSideBarPage.md). If this `Setting` has `showDefaultSetting == true`, then this method will also include the current `defaultSetting`.

Primarily intended for internal use.

```lua
local text = myObject:getMouseOverText()
```

**Returns**:

* `text` (string, nil): The text to display. Returning `nil` means that the `mouseOverInfo` should display text from a different source. e.g. from the `description` of the relevant [`SideBarPage`](./mwseMCMSideBarPage.md).

***

### `insertMouseovers`
<div class="search_terms" style="display: none">insertmouseovers</div>

Recursively walks over children of given `element` and inserts them into `self.mouseOvers`.

```lua
myObject:insertMouseovers(element)
```

**Parameters**:

* `element` ([tes3uiElement](../types/tes3uiElement.md))

***

### `makeComponent`
<div class="search_terms" style="display: none">makecomponent</div>

This method creates the border and inputField UI elements of the TextField.

```lua
myObject:makeComponent(parentBlock)
```

**Parameters**:

* `parentBlock` ([tes3uiElement](../types/tes3uiElement.md))

***

### `new`
<div class="search_terms" style="display: none">new</div>

Creates a new TextField.

```lua
local textField = myObject:new({ label = ..., buttonText = ..., variable = ..., numbersOnly = ..., description = ..., press = ..., sNewValue = ..., minHeight = ..., callback = ..., inGameOnly = ..., restartRequired = ..., restartRequiredMessage = ..., indent = ..., childIndent = ..., paddingBottom = ..., childSpacing = ..., postCreate = ..., class = ..., componentType = ..., parentComponent = ... })
```

**Parameters**:

* `data` (table): *Optional*.
	* `label` (string): *Optional*. Text shown above the text field.
	* `buttonText` (string): *Optional*. The text shown on the button next to the input field. The default text is a localized version of: "Submit".
	* `variable` ([mwseMCMVariable](../types/mwseMCMVariable.md), [mwseMCMSettingNewVariable](../types/mwseMCMSettingNewVariable.md)): *Optional*. A variable for this setting.
	* `numbersOnly` (boolean): *Default*: `false`. If true, only numbers will be allowed in this TextField.
	* `description` (string): *Optional*. If in a [Sidebar Page](../types/mwseMCMSideBarPage.md), the description will be shown on mouseover.
	* `press` (fun(self: [mwseMCMTextField](../types/mwseMCMTextField.md))): *Optional*. This allows overriding the default implementation of this method. Can be overriden to add a confirmation message before updating. This function should call `self:update()` at the end.
	* `sNewValue` (string): *Optional*. The message shown after a new value is submitted. This can be formatted with a '%s' which will be replaced with the new value. The default text is a localized version of: "New value: '%s'".
	* `minHeight` (integer): *Optional*. The minimum height set on the `self.element.border` UI element.
	* `callback` (fun(self: [mwseMCMTextField](../types/mwseMCMTextField.md))): *Optional*. This allows overriding the default implementation of this method. See its [description](../types/mwseMCMTextField.md#callback).
	* `inGameOnly` (boolean): *Default*: `false`. If true, the setting is disabled while the game is on main menu.
	* `restartRequired` (boolean): *Default*: `false`. If true, updating this Setting will notify the player to restart the game.
	* `restartRequiredMessage` (string): *Optional*. The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect."
	* `indent` (integer): *Default*: `12`. The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component.
	* `childIndent` (integer): *Optional*. The left padding size in pixels. Used on all the child components.
	* `paddingBottom` (integer): *Default*: `4`. The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component.
	* `childSpacing` (integer): *Optional*. The bottom border size in pixels. Used on all the child components.
	* `postCreate` (fun(self: [mwseMCMTextField](../types/mwseMCMTextField.md))): *Optional*. Can define a custom formatting function to make adjustments to any element saved in `self.elements`.
	* `class` (string): *Optional*.
	* `componentType` (string): *Optional*.
	* `parentComponent` ([mwseMCMComponent](../types/mwseMCMComponent.md)): *Optional*.

**Returns**:

* `textField` ([mwseMCMTextField](../types/mwseMCMTextField.md))

***

### `press`
<div class="search_terms" style="display: none">press</div>

Calls the `update` method.

```lua
myObject:press()
```

***

### `printComponent`
<div class="search_terms" style="display: none">printcomponent</div>

Prints the component table to the `mwse.log`. If a component is passed, it will be printed. If called without arguments, the component it was called on will be printed.

```lua
myObject:printComponent(component)
```

**Parameters**:

* `component` (table): *Default*: `self`.

***

### `registerMouseOverElements`
<div class="search_terms" style="display: none">registermouseoverelements</div>

Registers an event handler on each given UI element for the `tes3.uiEvent.mouseOver` and `tes3.uiEvent.mouseLeave` that will trigger "MCM:MouseOver" event. That event is used by the MCM to update the sidebar on the [mwseMCMSideBarPage](https://mwse.github.io/MWSE/types/mwseMCMSideBarPage/).

```lua
myObject:registerMouseOverElements(mouseOverList)
```

**Parameters**:

* `mouseOverList` ([tes3uiElement](../types/tes3uiElement.md)[]): *Optional*. If this argument isn't passed, does nothing.

***

### `resetToDefault`
<div class="search_terms" style="display: none">resettodefault</div>

This method will reset the `variable.value` to the default value.

```lua
myObject:resetToDefault()
```

***

### `setVariableValue`
<div class="search_terms" style="display: none">setvariablevalue, variablevalue</div>

Changes the TextField's `variable.value` to the given value, updates the TextField's label and widget, and calls `self:update`.

```lua
myObject:setVariableValue(newValue)
```

**Parameters**:

* `newValue` (string)

***

### `update`
<div class="search_terms" style="display: none">update</div>

Updates the variable's value to the current text in the text input element. If `self.numbersOnly` is true, it only allows setting the new value to a number.

```lua
myObject:update()
```

