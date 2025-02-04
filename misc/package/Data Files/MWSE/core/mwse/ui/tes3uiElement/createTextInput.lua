--
-- Provides lua-written extensions to text input widgets.
-- 
-- Overview:
-- 	- All inputs support basic common controls.
--  - All inputs focus when clicked on.
--  - All inputs support copy/paste.
--  - Inputs can be created to be numeric-only.
--  - Inputs can support placeholder text.
--

local common = require("mwse.common")

-- Much of this code was adapted from UI Expansion. As such we need to disable one of their modules.
local config = mwse.loadConfig("UI Expansion")
if (config and config.components and config.components.textInput) then
	config.components.textInput = false
	mwse.saveConfig("UI Expansion", config)
end

--- Prevents adding whitespace to placeholding elements.
--- @param e tes3uiEventData
--- @return boolean?
local function standardKeyPressBeforePlaceholding(e)
	local element = e.source
	local characterEntered = common.ui.eventCallbackHelper.getCharacterPressed(e)

	-- Prevent basically anything from happening if we are placeholding.
	local placeholding = element:getLuaData("mwse:placeholding") --- @type boolean
	if (placeholding and #string.trim(characterEntered or "") == 0) then
		return false
	end
end

--- Enforces that characters entered into the element remain numeric.
--- TODO: This can maybe be replaced by character substitution and tonumber, like with pasting.
--- @param e tes3uiEventData
--- @return boolean?
local function standardKeyPressBeforeNumeric(e)
	local element = e.source
	local characterEntered = common.ui.eventCallbackHelper.getCharacterPressed(e)

	if (not characterEntered or not element:getLuaData("mwse:numeric") or not tonumber(characterEntered)) then
		return
	end

	-- minus sign is okay so long as it's the first character
	if characterEntered == "-" then
		if element.text and #element.text > 0 then
			return false
		end
	-- periods are okay so long as there aren't any others 
	elseif characterEntered == "." then
		if element.text and element.text:find("%.") then
			return false
		end
	else
		return false
	end
end

--- Adds cut, copy, and paste support.
--- @param e tes3uiEventData
--- @return boolean?
local function standardKeyPressBeforeCutCopyPaste(e)
	local element = e.source
	local keyPressed = common.ui.eventCallbackHelper.getKeyPressed(e)
	local characterPressed = common.ui.eventCallbackHelper.getCharacterPressed(e)
	local inputController = tes3.worldController.inputController

	-- Handle copy/cut/paste.
	local isControlDown = inputController:isControlDown()
	local isAltDown = inputController:isAltDown()
	local isShiftDown = inputController:isShiftDown()
	local isSuperDown = inputController:isSuperDown()
	local keyData = { keyCode = characterPressed, isControlDown = isControlDown, isAltDown = isAltDown, isShiftDown = isShiftDown, isSuperDown = isSuperDown }
	local keyBindCopy = { keyCode = 'c', isControlDown = true, isShiftDown = false, isSuperDown = false }
	local isCopying = tes3.isKeyEqual({ actual = keyData, expected = keyBindCopy })
	local keyBindCut = { keyCode = 'x', isControlDown = true, isShiftDown = false, isSuperDown = false }
	local isCutting = tes3.isKeyEqual({ actual = keyData, expected = keyBindCut })
	local keyBindPaste = { keyCode = 'v', isAltDown = false, isControlDown = true, isShiftDown = false, isSuperDown = false }
	local isPasting = tes3.isKeyEqual({ actual = keyData, expected = keyBindPaste })
	if (isCopying or isCutting) then
		-- Figure out where our cursor is.
		local rawText = element.rawText
		local cursorPosition = rawText and string.find(rawText, "|", 1, true) or 0

		-- Figure out where we want to start copying. If we are holding alt, copy after the cursor. Otherwise copy up to it.
		local copyStart = isAltDown and (cursorPosition + 1) or 1
		local copyEnd = isAltDown and #rawText or (cursorPosition - 1)

		-- Copy our text.
		local copyText = string.sub(rawText, copyStart, copyEnd)
		if (not copyText or copyText == "") then
			return
		end
		os.setClipboardText(copyText)

		if (isCutting) then
			local cutText = string.sub(rawText, copyEnd + 1, #rawText)
			element.rawText = cutText
			element:getTopLevelMenu():updateLayout()
			element:triggerEvent(tes3.uiEvent.textUpdated)
		end

		return false
	elseif (isPasting) then
		-- Get clipboard text. 
		local clipboardText = os.getClipboardText()
		if (clipboardText == nil) then
			return false
		end

		-- Remove all instances of `|`.
		clipboardText = clipboardText and clipboardText:gsub("[|\r]", "")
		if (not clipboardText or clipboardText == "") then
			return false
		end

		local rawText = element.rawText
		local cursorPosition = rawText and string.find(rawText, "|", 1, true) or 1
		local newText = string.insert(rawText, clipboardText, cursorPosition - 1)

		-- Enforce numeric pasting.
		if (element:getLuaData("mwse:numeric") and tonumber(newText:gsub("|", "")) == nil) then
			return false
		end

		element.text = newText
		element:getTopLevelMenu():updateLayout()

		return false
	end
end

--- Allows deleting whole words, using ctrl+delete/backspace.
--- @param e tes3uiEventData
--- @return boolean?
local function standardKeyPressBeforeWordDeletion(e)
	local element = e.source
	local keyPressed = common.ui.eventCallbackHelper.getKeyPressed(e)
	local inputController = tes3.worldController.inputController

	local isControlDown = inputController:isControlDown()
	local isAltDown = inputController:isAltDown()
	local isShiftDown = inputController:isShiftDown()
	local isSuperDown = inputController:isSuperDown()
	local keyData = { keyCode = keyPressed, isControlDown = isControlDown, isAltDown = isAltDown, isShiftDown = isShiftDown, isSuperDown = isSuperDown }
	local keybindDeleteWordBehind = { keyCode = 0, isControlDown = true, isAltDown = false, isShiftDown = false, isSuperDown = false }
	local keybindDeleteWordAhead = { keyCode = 7, isControlDown = true, isAltDown = false, isShiftDown = false, isSuperDown = false }

	if (tes3.isKeyEqual({ actual = keyData, expected = keybindDeleteWordBehind })) then
		-- ctrl+backspace -> delete previous word
		element.rawText = element.rawText:gsub("(%w*[%W]*)|", "|")
		element:getTopLevelMenu():updateLayout()
		element:triggerEvent(tes3.uiEvent.textUpdated)
		return false
	elseif (tes3.isKeyEqual({ actual = keyData, expected = keybindDeleteWordAhead })) then
		-- ctrl+delete -> delete next word
		element.rawText = element.rawText:gsub("|(%w*[%W]*)", "|")
		element:getTopLevelMenu():updateLayout()
		element:triggerEvent(tes3.uiEvent.textUpdated)
		return false
	end
end

--- Allows improved control in text elements.
--- 	- Home goes to start.
--- 	- End goes to end.
--- 	- Ctrl+left and ctrl+right go to previous/next words.
--- @param e tes3uiEventData
--- @return boolean?
local function standardKeyPressBeforeCursorMovement(e)
	local element = e.source
	local keyPressed = common.ui.eventCallbackHelper.getKeyPressed(e)
	local inputController = tes3.worldController.inputController

	local isControlDown = inputController:isControlDown()
	local isAltDown = inputController:isAltDown()
	local isShiftDown = inputController:isShiftDown()
	local isSuperDown = inputController:isSuperDown()
	local keyData = { keyCode = keyPressed, isControlDown = isControlDown, isAltDown = isAltDown, isShiftDown = isShiftDown, isSuperDown = isSuperDown }
	local keybindMoveWordBehind = { keyCode = 1, isControlDown = true, isAltDown = false, isShiftDown = false, isSuperDown = false }
	local keybindMoveWordAhead = { keyCode = 2, isControlDown = true, isAltDown = false, isShiftDown = false, isSuperDown = false }
	local keybindMoveStart = { keyCode = 5, isControlDown = false, isAltDown = false, isShiftDown = false, isSuperDown = false }
	local keybindMoveEnd = { keyCode = 6, isControlDown = false, isAltDown = false, isShiftDown = false, isSuperDown = false }

	if (tes3.isKeyEqual({ actual = keyData, expected = keybindMoveWordBehind })) then
		-- ctrl+left -> move to previous word
		element.rawText = element.rawText:gsub("(%w*[%W]*)|", "|%1")
		element:getTopLevelMenu():updateLayout()
		return false
	elseif (tes3.isKeyEqual({ actual = keyData, expected = keybindMoveWordAhead })) then
		-- ctrl+right -> move to next word
		element.rawText = element.rawText:gsub("|(%w*[%W]*)", "%1|")
		element:getTopLevelMenu():updateLayout()
		return false
	elseif (tes3.isKeyEqual({ actual = keyData, expected = keybindMoveStart })) then
		-- home -> move cursor to start
		element.rawText = "|" .. element.rawText:gsub("|", "")
		element:getTopLevelMenu():updateLayout()
		return false
	elseif (tes3.isKeyEqual({ actual = keyData, expected = keybindMoveEnd })) then
		-- end -> move cursor to end
		element.rawText = element.rawText:gsub("|", "") .. "|"
		element:getTopLevelMenu():updateLayout()
		return false
	end
end

--- Standard pre-keyDown event callback that all text input share, at a reasonably high priority. Features include:
--- 	- Prevent garbage input when alt-tabbed.
--- 	- Enforce numeric values.
--- 	- Support placeholder text.
---		- Support for copy/paste.
--- @param e tes3uiEventData
--- @return boolean?
local function standardKeyPressBefore(e)
	local element = e.source
	local characterPressed = common.ui.eventCallbackHelper.getCharacterPressed(e)
	local inputController = tes3.worldController.inputController
	local isAltDown = inputController:isAltDown()

	-- Update previous text.
	element:setLuaData("mwse:previousText", element.text)

	-- Prevent tabs from inserting themselves for when alt-tabbing.
	if (characterPressed == '\t' and isAltDown) then
		return false
	end

	-- Are we in the placeholder state? Prevent garbage inputs.
	local result = standardKeyPressBeforePlaceholding(e)
	if (result ~= nil) then
		return result
	end

	-- Handle numeric restrictions.
	result = standardKeyPressBeforeNumeric(e)
	if (result ~= nil) then
		return result
	end

	-- Allow cut/copy/paste.
	result = standardKeyPressBeforeCutCopyPaste(e)
	if (result ~= nil) then
		return result
	end

	-- Allow control+backspace/delete to delete previous/next word.
	result = standardKeyPressBeforeWordDeletion(e)
	if (result ~= nil) then
		return result
	end

	-- Allow cursor movement via special keys.
	result = standardKeyPressBeforeCursorMovement(e)
	if (result ~= nil) then
		return result
	end
end

--- Standard post-keyDown event callback that all text input share, at a reasonably high priority.
--- @param e tes3uiEventData
local function standardKeyPressAfter(e)
	local element = e.source

	-- Raise textUpdated event.
	local previousText = element:getLuaData("mwse:previousText") --- @type string?
	if (element.text ~= previousText) then
		element:triggerEvent(tes3.uiEvent.textUpdated)
	end

	element:getTopLevelMenu():updateLayout()
end

--- Standard post-keyDown event callback that all text input share, at a reasonably high priority.
--- @param e tes3uiEventData
local function onTextInputFocus(e)
	local element = e.source

	local placeholding = element:getLuaData("mwse:placeholding")
	local hasCursor = (element.rawText:find("|", 1, true) ~= nil)
	if (not placeholding and not hasCursor) then
		local lastIndex = element:getLuaData("mwse:lastCursorIndex") or #element.text
		element.rawText = string.insert(element.rawText, "|", lastIndex - 1)
		element:setLuaData("mwse:lastCursorIndex", nil)
		element:getTopLevelMenu():updateLayout()
	end
end

--- Standard post-keyDown event callback that all text input share, at a reasonably high priority.
--- @param e tes3uiEventData
local function onTextInputUnfocus(e)
	local element = e.source
	element:setLuaData("mwse:lastCursorIndex", element.rawText:find("|", 1, true))
	element.rawText = element.rawText:gsub("|", "")
	element:getTopLevelMenu():updateLayout()
end

--- @param e tes3uiEventData
local function onTextUpdated(e)
	local element = e.source

	local placeholding = element:getLuaData("mwse:placeholding")
	local placeholderText = element:getLuaData("mwse:placeholderText")

	-- Make sure a text cleared event fires.
	if (element.text == "") then
		-- Raise textCleared event.
		element:triggerEvent(tes3.uiEvent.textCleared)
		element:setLuaData("mwse:previousText", nil)
		return
	elseif (placeholding and element.text ~= placeholderText) then
		-- Unset placeholding.
		element.color = tes3ui.getPalette("normal_color")
		element:setLuaData("mwse:placeholding", false)
	end
end

--- @param e tes3uiEventData
local function onTextCleared(e)
	local element = e.source

	-- Check if we need to change back to placeholder text.
	local placeholderText = element:getLuaData("mwse:placeholderText") --- @type string?
	if (placeholderText) then
		element.text = placeholderText
		element.color = tes3ui.getPalette("disabled_color")
		element:setLuaData("mwse:placeholding", true)
		return
	end
end

--- @param element tes3uiElement
local function setupTextInput(element)
	-- More sane default values.
	element.widget.lengthLimit = nil

	-- Register some standard events, to improve input mapping, provide copy/paste support, and prevent garbage input.
	element:registerBefore(tes3.uiEvent.keyPress, standardKeyPressBefore, 1000)
	element:registerAfter(tes3.uiEvent.keyPress, standardKeyPressAfter, 1000)
	element:registerAfter(tes3.uiEvent.inputFocus, onTextInputFocus)
	element:registerAfter(tes3.uiEvent.inputUnfocus, onTextInputUnfocus)
	element:registerAfter(tes3.uiEvent.textUpdated, onTextUpdated, -1000)
	element:registerAfter(tes3.uiEvent.textCleared, onTextCleared)
end

--- @diagnostic disable-next-line
function tes3uiElement:createTextInput(params)
	params = params or {}

	local parent = self
	if (params.createBorder) then
		parent = self:createThinBorder({ id = "MWSE:TextInputBorder"})
		parent.autoHeight = true
		parent.autoWidth = true
		parent.paddingLeft = 5
		parent.paddingRight = 5
		parent.paddingTop = 3
		parent.paddingBottom = 5
		parent.widthProportional = 1.0
		parent.consumeMouseEvents = true
	end

	-- With the below code to override all text inputs with standard features, we just need to create a normal text input.
	local element = parent:_createTextInput(params) ---@diagnostic disable-line

	-- Basic property setting.
	if (params.text) then
		element.text = params.text
	else
		element.rawText = ""
	end

	-- Allow placeholder text.
	local placeholderText = params.placeholderText
	if (placeholderText) then
		element:setLuaData("mwse:placeholderText", placeholderText)

		-- If we weren't given text, set to the placeholder text.
		if (params.text == nil) then
			element.text = placeholderText
		end

		-- Fix color if we are using the placeholder text.
		if (element.text == placeholderText) then
			element.color = tes3ui.getPalette(tes3.palette.disabledColor)
			element:setLuaData("mwse:placeholding", true)
		end

		element.widget.eraseOnFirstKey = true
	end

	-- Only allow numbers.
	if (params.numeric) then
		element:setLuaData("mwse:numeric", true)
	end

	-- Handle focus.
	element:registerAfter(tes3.uiEvent.mouseClick, common.ui.eventCallback.acquireTextInput)
	if (params.createBorder) then
		element.parent:registerAfter(tes3.uiEvent.mouseClick, function()
			tes3ui.acquireTextInput(element)
		end)
	end

	-- Allow automatically focusing the newly created element.
	if (params.autoFocus) then
		tes3ui.acquireTextInput(element)
	end

	return element
end

-- 
-- Patch: Make existing text inputs support new features.
-- 

--- @param element tes3uiElement
local function patchVanillaTextInputs(element, _, keyPressCallback, _)
	-- Call overwritten code.
	element:register(tes3.uiEvent.keyPress, keyPressCallback)

	-- Setup our element to register common controls.
	setupTextInput(element)
end

--- @diagnostic disable-next-line
assert(mwse.memory.writeFunctionCall({
	address = 0x64AA5A,
	previousCall = 0x581F30,
	signature = {
		this = "tes3uiElement",
		arguments = { "uint", "uint", "uint" },
	},
	call = patchVanillaTextInputs,
}), "Could not hook existing text input UI creation!")
