# niColorData
<div class="search_terms" style="display: none">nicolordata, colordata</div>

<!---
	This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
	More information: https://github.com/MWSE/MWSE/tree/master/docs
-->

The NiColorData class provides a shareable wrapper for color animation data. Usually found in niParticleColorModifiers.

This type inherits the following: [niObject](../types/niObject.md).
## Properties

### `keyCount`
<div class="search_terms" style="display: none">keycount</div>

The number of keys in this niColorData.

**Returns**:

* `result` (integer)

***

### `keys`
<div class="search_terms" style="display: none">keys</div>

*Read-only*. The keyframe data that this object currently stores.

**Returns**:

* `result` ([niColorKey](../types/niColorKey.md)[])

***

### `keyType`
<div class="search_terms" style="display: none">keytype</div>

The type of the keys. Maps to values in [`ni.animationKeyType`](https://mwse.github.io/MWSE/references/ni/animation-key-types/) table.

**Returns**:

* `result` ([ni.animationKeyType](../references/ni/animation-key-types.md))

***

### `refCount`
<div class="search_terms" style="display: none">refcount</div>

*Read-only*. The number of references that exist for this object. When this value reaches zero, the object will be deleted.

**Returns**:

* `result` (number)

***

### `RTTI`
<div class="search_terms" style="display: none">rtti</div>

*Read-only*. The runtime type information for this object. This is an alias for the `.runTimeTypeInformation` property.

**Returns**:

* `result` ([niRTTI](../types/niRTTI.md))

***

### `runTimeTypeInformation`
<div class="search_terms" style="display: none">runtimetypeinformation</div>

*Read-only*. The runtime type information for this object.

**Returns**:

* `result` ([niRTTI](../types/niRTTI.md))

***

## Methods

### `clone`
<div class="search_terms" style="display: none">clone</div>

Creates a copy of this object.

```lua
local result = myObject:clone()
```

**Returns**:

* `result` ([niObject](../types/niObject.md))

***

### `isInstanceOfType`
<div class="search_terms" style="display: none">isinstanceoftype, instanceoftype</div>

Determines if the object is of a given type, or of a type derived from the given type.

```lua
local result = myObject:isInstanceOfType(type)
```

**Parameters**:

* `type` ([ni.type](../references/ni/types.md)): Use values in the [`ni.type`](https://mwse.github.io/MWSE/references/ni/types/) table.

**Returns**:

* `result` (boolean)

***

### `isOfType`
<div class="search_terms" style="display: none">isoftype, oftype</div>

Determines if the object is of a given type.

```lua
local result = myObject:isOfType(type)
```

**Parameters**:

* `type` ([ni.type](../references/ni/types.md)): Use values in the [`ni.type`](https://mwse.github.io/MWSE/references/ni/types/) table.

**Returns**:

* `result` (boolean)

***

### `saveBinary`
<div class="search_terms" style="display: none">savebinary</div>

Serializes the object, and writes it to the given file.

```lua
local success = myObject:saveBinary(path)
```

**Parameters**:

* `path` (string): The path to write the file at, relative to the Morrowind installation folder. The `.nif` extension needs to be specified manually.

**Returns**:

* `success` (boolean): If true the object was successfully serialized.

