return {
	type = "method",
	description = [[Sets an `event` handler, which can add or override an existing event handler. The use of `registerBefore` or `registerAfter` is recommended if you do not want to replace the existing event handler. The eventID can be a standard `event` name, or an event specific to an element class. These can be accessed through [`tes3.uiEvent`](https://mwse.github.io/MWSE/references/ui-events/) for convenience. The callback receives an argument with the event data. See below for details.

The original Morrowind callback is captured and can be invoked with the `forwardEvent` method on the event argument. If there is an existing Lua callback, it is replaced.

Standard events:

* **mouseLeave**
	Mouse cursor moving outside an element. Triggers once.
* **mouseOver**
	Mouse cursor moving over an element. Triggers once.
* **mouseDown**
	Left mouse button down over an element.
* **mouseClick**
	Left mouse button up over an element, after a mouseDown over the element.
* **mouseScrollUp**
	Mouse wheel scrolling.
* **mouseScrollDown**
	Mouse wheel scrolling.
* **mouseDoubleClick**
	Standard double-click.
* **mouseStillIdle**
	Mouse cursor positioned outside an element. Triggers every frame.
* **mouseStillOver**
	Mouse cursor positioned over an element. Triggers every frame.
* **mouseStillPressed**
	Mouse cursor positioned over an element, after a mouseDown over the element. Triggers every frame.
* **mouseStillPressedOutside**
	Apparently not working in the engine. Mouse cursor positioned outside an element, after a mouseDown over the element. Triggers every frame.
* **mouseRelease**
	Left mouse button up over an element.
* **keyPress**
	A raw key press.
* **keyEnter**
	The Return key is pressed.
* **help**
	On mouseover, but also marking the element as having a tooltip. Create a tooltip within the callback using the `tes3ui.createTooltipMenu` function.
* **focus**
	When a menu is clicked on, and moved on top of other menus.
* **unfocus**
	Just before another menu is clicked on, or a widget in that menu receives an event, or when the menu mode is toggled off. You may return false from this event to prevent the menu from being deselected, and to prevent leaving menu mode.
* **preUpdate**
	Before the menu layout is updated.
* **update**
	After the menu layout is updated.
* **destroy**
	When the UI element is destroyed, before any data or children are destroyed.

Widget-specific events:

* Slider:
	* **PartScrollBar_changed**
		Triggers on value change; moving the slider is not enough if the value is the same.

#### Event forwarding
***

The original Morrowind event handler is saved when you first register an event. It may be optionally invoked with the `forwardEvent` method. Note that handler may or may not destroy the event widget or the menu, so you should know how it behaves before accessing any elements after a callback.

**Example**
```lua
---@param e tes3uiEventData
---@return boolean? block
local function onClick(e)
	-- pre-event code
	e.source:forwardEvent(e)
	-- post-event code
end

local button = menu:findChild("MenuExample_Ok")
button:register(tes3.uiEvent.mouseClick, onClick)
```
]],
	arguments = {
		{ name = "eventID", type = "tes3.uiEvent", description = "The event id. Maps to values in [`tes3.uiEvent`](https://mwse.github.io/MWSE/references/ui-events/)." },
		{ name = "callback", type = "integer|fun(e: tes3uiEventData): boolean?", description = "The callback function. Returning `false` from this function may cancel an interaction for certain events, such as unfocus." },
	},
}