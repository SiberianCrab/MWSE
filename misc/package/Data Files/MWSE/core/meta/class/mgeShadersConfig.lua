--- @meta

-- This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
-- More information: https://github.com/MWSE/MWSE/tree/master/docs

--- Allows control of MGE shader features.
--- @class mgeShadersConfig
--- @field debug string *Read-only*. Gathers a string listing all shaders.
--- @field hdrReactionSpeed number The HDR exposure reaction speed, in seconds.
--- @field list mgeShaderHandle[] *Read-only*. Loads a list of all shaders. This is not a constant-held collection, and each shader handle is initialized anew each time this function is called. Cache this value when you are sure that shaders are not added or removed.
mgeShadersConfig = {}

--- Finds a loaded shader and returns a handle to it.
--- @param params mgeShadersConfig.find.params This table accepts the following values:
--- 
--- `name`: string — No description yet available.
--- @return mgeShaderHandle|nil shader No description yet available.
function mgeShadersConfig.find(params) end

---Table parameter definitions for `mgeShadersConfig.find`.
--- @class mgeShadersConfig.find.params
--- @field name string No description yet available.

--- Loads a shader by name, from the `Data Files/shaders/XEshaders` directory. Adds the shader to the existing shader list, or returns the existing shader if it is already loaded.
--- 
--- If the shader has a category annotation, it is inserted into a position that preserves the category ordering. Shaders without a category will be added to the end of the list.
--- 
--- Summary of category sort order:
--- 
--- * scene: Additional objects rendered into the scene.
--- * atmosphere: Atmosphere effects that render over all objects, such as mist.
--- * lens: Lens effects such as depth of field.
--- * sensor: Sensor effects such as bloom.
--- * tone: Tone mapping and color grading.
--- * final: Any effects that need to run last.
--- @param params mgeShadersConfig.load.params This table accepts the following values:
--- 
--- `name`: string — No description yet available.
--- @return mgeShaderHandle|nil shader No description yet available.
function mgeShadersConfig.load(params) end

---Table parameter definitions for `mgeShadersConfig.load`.
--- @class mgeShadersConfig.load.params
--- @field name string No description yet available.

