--[[
	Slider:
		A Slider Setting
		Combines a text label with a slider widget. For tes3uiSlider the value range is [0, max].
		MCM sliders allow specifying minimal value different than 0. The implementation adds/subtracts
		`self.min` when reading/writing to the current tes3uiSlider's `widget.current` to account for
		that offset (so tes3uiSlider's value range is [0, self.max - self.min]). In addition, children
		may implement support for floating point values. This is accomplished by keeping the MCM slider's
		variable in the desired floating point range and scaling it in `scaleToSliderRange` and
		`scaleToVariableRange` methods when reading/writing to integer range used by the underlying
		tes3uiSlider.

		Usually, children of this component implement some of the following methods:
		- scaleToVariableRange - to convert from tes3uiSlider value range to variable's range
		- scaleToSliderRange - to convert from variable value range to tes3uiSlider's range
		- getNewValue - to read current from `self.elements.slider.widget.current` and convert that to range used by the variable
		- updateValueLabel - to update `self.elements.label.text` based on newly-set `self.elements.slider.widget.current`
		- getCurrentWidgetValue - to read current `self.variable.value` and convert that to the range of values used by slider widget
]]--

--- These types have annotations in the core\meta\ folder. Let's stop the warning spam here in the implementation.
--- The warnings arise because each field set here is also 'set' in the annotations in the core\meta\ folder.
--- @diagnostic disable: duplicate-set-field

local Parent = require("mcm.components.settings.Setting")

--- @class mwseMCMSlider
local Slider = Parent:new()
Slider.min = 0
Slider.max = 100
Slider.step = 1
Slider.jump = 5

function Slider:scaleToSliderRange(value)
	return value
end

function Slider:scaleToVariableRange(value)
	return value
end

function Slider:getNewValue()
	local newValue = self.elements.slider.widget.current
	return self:scaleToVariableRange(newValue) + self.min
end

function Slider:updateValueLabel()
	local newValue = ""
	local labelText = ""

	if self.elements.slider then
		newValue = tostring(self:getNewValue())
	end

	if string.find(self.label, "%s", 1, true) then
		labelText = string.format(self.label, newValue)
	else
		labelText = self.label .. ": " .. newValue
	end

	self.elements.label.text = labelText

end

function Slider:update()
	self.variable.value = self:getNewValue()
	Parent.update(self)
end

--- @param element tes3uiElement
function Slider:registerSliderElement(element)
	-- click
	element:register(tes3.uiEvent.mouseClick, function(e)
		self:update()
	end)
	-- drag
	element:register(tes3.uiEvent.mouseRelease, function(e)
		self:update()
	end)
end

function Slider:getCurrentWidgetValue()
	local newValue = self.variable.value - self.min
	return self:scaleToSliderRange(newValue)
end

function Slider:enable()
	Parent.enable(self)
	if self.variable.value then
		self.elements.slider.widget.current = self:getCurrentWidgetValue()
		self:updateValueLabel()
	end

	-- Register slider elements so that the value only updates when the mouse is released
	for _, sliderElement in ipairs(self.elements.slider.children) do
		self:registerSliderElement(sliderElement)
		for _, innerElement in ipairs(sliderElement.children) do
			self:registerSliderElement(innerElement)
		end
	end

	-- But we want the label to update in real time so you can see where it's going to end up
	self.elements.slider:register(tes3.uiEvent.partScrollBarChanged, function(e)
		self:updateValueLabel()
	end)
end

function Slider:disable()
	Parent.disable(self)

	self.elements.slider.children[2].children[1].visible = false
	-- self.elements.sliderValueLabel.color = tes3ui.getPalette("disabled_color")

end

-- UI creation functions

--- @param parentBlock tes3uiElement
function Slider:createOuterContainer(parentBlock)
	Parent.createOuterContainer(self, parentBlock)
	self.elements.outerContainer.borderRight = self.indent -- * 2
end

--- @param parentBlock tes3uiElement
function Slider:createLabel(parentBlock)
	Parent.createLabel(self, parentBlock)
	self:updateValueLabel()
	--[[self.elements.label.autoWidth = true
	self.elements.label.widthProportional = nil
	self.elements.labelBlock.flowDirection = "left_to_right"

	local sliderValueLabel = self.elements.labelBlock:createLabel({text = ": --" })
	self.elements.sliderValueLabel = sliderValueLabel
	table.insert(self.mouseOvers, sliderValueLabel)]] --
end

--- @param parentBlock tes3uiElement
function Slider:makeComponent(parentBlock)
	local sliderBlock = parentBlock:createBlock()
	sliderBlock.flowDirection = tes3.flowDirection.leftToRight
	sliderBlock.autoHeight = true
	sliderBlock.widthProportional = 1.0
	local range = self:scaleToSliderRange(self.max - self.min)
	local slider = sliderBlock:createSlider({ current = 0, max = range })
	slider.widthProportional = 1.0

	-- Set custom values from setting data
	slider.widget.step = self:scaleToSliderRange(self.step)
	slider.widget.jump = self:scaleToSliderRange(self.jump)

	self.elements.slider = slider
	self.elements.sliderBlock = sliderBlock

	-- add mouseovers
	table.insert(self.mouseOvers, sliderBlock)
	-- Add every piece of the slider to the mouseOvers
	for _, sliderElement in ipairs(slider.children) do
		table.insert(self.mouseOvers, sliderElement)
		for _, innerElement in ipairs(sliderElement.children) do
			table.insert(self.mouseOvers, innerElement)
		end
	end
end

return Slider
