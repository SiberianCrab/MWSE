--- MCP feature Dependency - checks if given list of MCP features are on/off
---@class MWSE.Metadata.Dependency.MCP : MWSE.Metadata.Dependency
---@field features table<string, boolean> A dictionary of needed MCP features and their on/off states


--- Inspired by this thread: https://lua-users.org/lists/lua-l/2006-01/msg00231.html
---@param enumName string
local function splitCamelCase(enumName)
	-- Make the first letter uppercase
	enumName = enumName:gsub("^%l", string.upper)
	-- Insert space between lowercase and uppercase character
	enumName = enumName:gsub( "(%l)(%u)", "%1 %2" )
	return enumName
end

---@param enum string
---@param descriptions table|nil
local function getFeatureName(enum, descriptions)
	if not descriptions then
		return splitCamelCase(enum)
	end

	local id = tes3.codePatchFeature[enum]
	for _, category in ipairs(descriptions) do
		for _, patch in ipairs(category.patches) do
			if patch.id == id then
				return string.format("%s (%s)", patch.brief, category.category)
			end
		end
	end

	-- If the given feature isn't present in the describe.json fall back to the generalized solution
	return splitCamelCase(enum)
end

local mcpDescribePath = "..\\..\\mcpatch\\describe.json"

---@param dependencyManager DependencyManager
---@param dependency MWSE.Metadata.Dependency.MCP
local function check(dependencyManager, dependency)
	local missingFeatures = {}
	local descriptions = json.loadfile(mcpDescribePath)

	for feature, needed in pairs(dependency.features) do
		local id = tes3.codePatchFeature[feature]
		if not id then
			dependencyManager.logger:error("Unknown MCP feature: %s.", feature)
		else
			local hasFeature = tes3.hasCodePatchFeature(id)
			if hasFeature ~= needed then
				local message = needed and [["%s" needs to be enabled.]] or [["%s" needs to be disabled.]]
				missingFeatures[#missingFeatures + 1] = string.format(message, getFeatureName(feature, descriptions))
			end
		end
	end

	if table.size(missingFeatures) > 0 then
		return false, {{
			title = "Some MCP feature(s) are needed:",
			reasons = missingFeatures
		}}
	end

	return true
end

return {
	id = "mcp",
	checkDependency = check
}
