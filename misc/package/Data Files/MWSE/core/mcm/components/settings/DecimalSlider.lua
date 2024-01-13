--[[
	DecimalSlider:
		A Slider Setting that supports decimal numbers with specified
		amount of decimal places. The underlying implementation has
		a slider in range (min * 10 ^ decimalPlaces, max * 10 ^ decimalPlaces),
		while the label above the slider converts that to the decimal.
]]--

--- These types have annotations in the core\meta\ folder. Let's stop the warning spam here in the implementation.
--- The warnings arise because each field set here is also 'set' in the annotations in the core\meta\ folder.
--- @diagnostic disable: duplicate-set-field

local Parent = require("mcm.components.settings.Slider")
local Setting = require("mcm.components.settings.Setting")

--- @class mwseMCMDecimalSlider
local DecimalSlider = Parent:new()
DecimalSlider.min = 0.0
DecimalSlider.max = 1.0
DecimalSlider.step = 0.01
DecimalSlider.jump = 0.05
DecimalSlider.decimalPlaces = 2

--- @param number number
local function isPositiveInteger(number)
	return (number % 1 == 0) and (number > 0)
end

--- @param data mwseMCMDecimalSlider.new.data?
--- @return mwseMCMDecimalSlider slider
function DecimalSlider:new(data)
	local t = data or {}
	t.max = t.max or self.max
	t.min = t.min or self.min
	t.step = t.step or self.step
	t.jump = t.jump or self.jump
	t.decimalPlaces = t.decimalPlaces or self.decimalPlaces

	assert(isPositiveInteger(t.decimalPlaces), "Invalid 'decimalPlaces' parameter provided. It must be an integer greater than 0.")

	t.max  = t.max  * 10 ^ t.decimalPlaces
	t.min  = t.min  * 10 ^ t.decimalPlaces
	t.step = t.step * 10 ^ t.decimalPlaces
	t.jump = t.jump * 10 ^ t.decimalPlaces

	if data and data.variable then
		-- create setting variable
		t.variable.defaultSetting = t.variable.defaultSetting or t.defaultSetting
		local typePath = ("mcm.variables." .. t.variable.class)
		t.variable = require(typePath):new(t.variable)
	end

	if t.parentComponent then
		t.indent = t.parentComponent.childIndent or t.indent
		t.paddingBottom = t.parentComponent.childSpacing or t.paddingBottom
	end

	setmetatable(t, self)
	self.__index = self
	--- @cast t mwseMCMDecimalSlider
	return t
end

function DecimalSlider:updateValueLabel()
	local newValue = 0
	local labelText = ""

	if self.elements.slider then
		newValue = (self.elements.slider.widget.current + self.min) / 10 ^ self.decimalPlaces
	end

	if string.find(self.label, "%", 1, true) then
		labelText = string.format(self.label, newValue)
	else
		labelText = self.label .. string.format(string.format(": %%.%uf", self.decimalPlaces), newValue)
	end

	self.elements.label.text = labelText
end

function DecimalSlider:update()
	local newValue = (self.elements.slider.widget.current + self.min) / 10 ^ self.decimalPlaces
	self.variable.value = newValue
	
	-- Bypass Slider:update to avoid overwriting the variable with an unscaled value.
	Setting.update(self)
end

function DecimalSlider:enable()
	Parent.enable(self)
	if self.variable.value then
		self.elements.slider.widget.current = (self.variable.value * 10 ^ self.decimalPlaces) - self.min
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

return DecimalSlider
