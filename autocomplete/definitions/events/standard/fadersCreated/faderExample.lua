-- This is a working example. You are encouraged to create a new file
-- main.lua, paste this code and see the results in-game!
-- Use `u` key to activate the fader.
-- Use `l` and `k` keys to increase or decrease the fader's opacity.

-- This variable is used to store our fader.
local fader = nil

local function createFader()
	fader = tes3fader.new()
	fader:setColor({
		-- This changes the color of our fader to green.
		-- The RGB values are in range [0.0, 1.0].
		color = { 0.0, 1.0, 0.0 },
	})

	-- The fader needs to be updated every frame to be rendered correctly.
	-- You may notice that for this event we have registered a function with
	-- no name. That is an anonymous function. It works exactly the same as
	-- any other function. We have a need to register this function inside
	-- our createFader() function, since our `fader` variable is `nil` at start
	-- (look up). We can't call fader:update() if fader is `nil`.
	event.register(tes3.event.enterFrame, function()
		fader:update()
	end)
end

-- The fader needs to be created during `fadersCreated` event,
-- so our createFader() function is registered for that event.
event.register(tes3.event.fadersCreated, createFader)


local opacity = 0.1

local function activateFader()
	-- The fader needs to be activated first to be visible.
	fader:activate()
	-- Now we change its visibility.
	fader:fadeTo({
		value = opacity,
		duration = 3,
	})
	tes3.messageBox("Welcome to the Fallout mode!")
end

-- We registered our activateFader() function on keyDown event, filtered for `u` key.
-- That makes our activateFader() function called only when `u` is pressed.
event.register(tes3.event.keyDown, activateFader, { filter = tes3.scanCode.u })

local function increaseOpacity()
	-- The fader's opacity is in [0.0, 1.0] range.
	-- Make sure we don't exceed it.
	if opacity <= 0.9 then
		opacity = opacity + 0.1
	else
		return
	end
	-- This method sets the current opacity of our fader
	-- to the value of `opacity` variable
	fader:updateMaterialProperty(opacity)

	-- The "\n" sign means insert a new line here.
	-- The "%.1f" code means insert the opacity's value in this text.
	-- The ".1" part means show 1 decimal after the decimal point.
	tes3.messageBox("Fader opacity increased.\nCurrent opacity: %.1f", opacity)
end
event.register(tes3.event.keyDown, increaseOpacity, { filter = tes3.scanCode.l })

local function decreaseOpacity()
	if opacity >= 0.1 then
		opacity = opacity - 0.1
	else
		return
	end
	fader:updateMaterialProperty(opacity)
	tes3.messageBox("Fader opacity decreased.\nCurrent opacity: %.1f", opacity)
end
event.register(tes3.event.keyDown, decreaseOpacity, { filter = tes3.scanCode.k })
