local function doMyRayTest()
	-- the result can get invalidated
	local result = tes3.rayTest({
		position = tes3.getPlayerEyePosition(),
		direction = tes3.getPlayerEyeVector(),
		ignore = { tes3.player }
	})

	if not result then
		return
	end

	local refHandle = tes3.makeSafeObjectHandle(result.reference)
	timer.start({
		type = timer.simulate,
		duration = 20,
		iterations = 1,
		callback = function()
			-- Before using the reference, we need to check that it's still valid.
			-- References get unloaded on cell changes etc.
			if not refHandle:valid() then
				return
			end
			local reference = refHandle:getObject()
			-- Now we can use the `reference` variable safely
			-- ...
		end
	})
end
