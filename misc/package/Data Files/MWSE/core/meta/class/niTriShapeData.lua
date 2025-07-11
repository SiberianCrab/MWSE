--- @meta

-- This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
-- More information: https://github.com/MWSE/MWSE/tree/master/docs

--- Contains the geometry data for an `NiTriShape` object.
--- @class niTriShapeData : niTriBasedGeometryData, niGeometryData, niObject
--- @field triangles niTriangle[] The access to the triangles of the object. The length of the array is equal to the number of active triangles.
niTriShapeData = {}

--- Creates a copy of the data. An optional table of filters can be passed to remove information from the copy.
--- @param filters? niTriShapeData.copy.filters This table accepts the following values:
--- 
--- `normals?`: boolean — *Default*: `true`. If false, the geometry data's normals will be absent from the copy.
--- 
--- `colors?`: boolean — *Default*: `true`. If false, the geometry data's colors will be absent from the copy.
--- 
--- `texCoords?`: boolean — *Default*: `true`. If false, the geometry data's texture coordinates will be absent from the copy.
--- @return niTriShapeData copiedData The duplicated data.
function niTriShapeData:copy(filters) end

---Table parameter definitions for `niTriShapeData.copy`.
--- @class niTriShapeData.copy.filters
--- @field normals? boolean *Default*: `true`. If false, the geometry data's normals will be absent from the copy.
--- @field colors? boolean *Default*: `true`. If false, the geometry data's colors will be absent from the copy.
--- @field texCoords? boolean *Default*: `true`. If false, the geometry data's texture coordinates will be absent from the copy.

