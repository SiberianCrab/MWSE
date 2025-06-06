# tes3vector3
<div class="search_terms" style="display: none">tes3vector3, vector3</div>

<!---
	This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
	More information: https://github.com/MWSE/MWSE/tree/master/docs
-->

A simple trio of floating-point numbers.

## Properties

### `b`
<div class="search_terms" style="display: none">b</div>

The third value in the vector. An alias for `z`.

**Returns**:

* `result` (number)

***

### `g`
<div class="search_terms" style="display: none">g</div>

The second value in the vector. An alias for `y`.

**Returns**:

* `result` (number)

***

### `r`
<div class="search_terms" style="display: none">r</div>

The first value in the vector. An alias for `x`.

**Returns**:

* `result` (number)

***

### `x`
<div class="search_terms" style="display: none">x</div>

The first value in the vector.

**Returns**:

* `result` (number)

***

### `y`
<div class="search_terms" style="display: none">y</div>

The second value in the vector.

**Returns**:

* `result` (number)

***

### `z`
<div class="search_terms" style="display: none">z</div>

The third value in the vector.

**Returns**:

* `result` (number)

***

## Methods

### `__tostring`
<div class="search_terms" style="display: none">__tostring</div>

Converts the vector to a string with 2 decimal places.

```lua
local result = myObject:__tostring()
```

**Returns**:

* `result` (string)

***

### `angle`
<div class="search_terms" style="display: none">angle</div>

The returns the angle between the two vectors in radians.

```lua
local result = myObject:angle(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

***

### `copy`
<div class="search_terms" style="display: none">copy</div>

Creates a copy of the vector.

```lua
local result = myObject:copy()
```

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `cross`
<div class="search_terms" style="display: none">cross</div>

Calculates the cross product with another vector.

```lua
local result = myObject:cross(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `distance`
<div class="search_terms" style="display: none">distance</div>

Calculates the distance to another vector in the standard way, i.e., using the [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance).

```lua
local result = myObject:distance(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

***

### `distanceChebyshev`
<div class="search_terms" style="display: none">distancechebyshev</div>

Calculates the distance to another vector, using the [Chebyshev metric](https://en.wikipedia.org/wiki/Chebyshev_distance), which is defined as

	math.max(math.abs(v1.x - v2.x), math.abs(v1.y - v2.y), math.abs(v1.z - v2.z))

This is useful for ensuring that the x, y, and z coordinates between two vectors are all (independently) within a certain distance from each other.

Here is a geometric description of the difference between the normal distance and the Chebyshev distance for two `tes3vector3`s  `v1` and `v2`:

* If `v1:distance(v2) <= 1`, then `v2` is contained in a sphere around `v1` with radius 1 (i.e. diameter 2).
* If `v1:distanceChebyshev(v2) <= 1`, then `v2` is contained within a cube centered around `v1`, where the cube has length 2.


```lua
local result = myObject:distanceChebyshev(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

***

### `distanceManhattan`
<div class="search_terms" style="display: none">distancemanhattan</div>

Calculates the distance to another vector, using the [Manhattan (i.e. city block) metric](https://en.wikipedia.org/wiki/Taxicab_geometry). 
In the two-dimensional case, the Manhattan metric can be thought of 
as the distance that two taxis will have to travel if they're following a grid system.
The formula for the Manhattan distance is

	math.abs(v1.x - v2.x) + math.abs(v1.y - v2.y) + math.abs(v1.z - v2.z)

This is useful for checking how far you'd actually have to move if you're only allowed to move along one axis at a time.


```lua
local result = myObject:distanceManhattan(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

***

### `distanceXY`
<div class="search_terms" style="display: none">distancexy</div>

Calculates the distance between the XY-coordinates of two vectors.

This method offers a way of calculating distances between vectors in situations where it's more convenient to ignore the z-coordinates.


```lua
local result = myObject:distanceXY(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

??? example "Example: Items on bookshelves."

	Let's say you want to make a function that checks if two ingredients are close together. This will involve looking at the distance between two `tes3reference`s.

	One way to do this would be to use the normal `tes3vector3:distance` method, but this has a drawback: it doesn't work consistently with ingredients on bookshelves. If two ingredients are on the same shelf, their `z`-coordinates contribute very little to the distance between them, while the situation is reversed for ingredients on different shelves.

	This problem is remedied by using `tes3vector3:distanceXY` as follows:

	```lua
	-- Check if two items are on the same bookshelf
	---@param ref1 tes3reference reference to one ingredient
	---@param ref2 tes3reference reference to another ingredient
	local function isOnSameShelf(ref1, ref2)
		local maxDistXY = 75 -- XY tolerance
		local maxDistZ = 150 -- Z tolerance
	
		-- distanceXY ignores the Z coordinate, which has the effect of 
		-- "pretending" `ref1` and `ref2` are on the same shelf
		local distanceXY = ref1.position:distanceXY(ref2.position)
		-- check the height difference separately, to make sure it's not too crazy 
		-- for example, if we're inside a building, this would make sure that 
		--  `ref1` and `ref2` are on the same floor of the building.
		local distanceZ = ref1.position:heightDifference(ref2.position)
	
		return distanceXY <= maxDistXY and distanceZ <= maxDistZ
	end

	```

***

### `dot`
<div class="search_terms" style="display: none">dot</div>

Calculates the dot product with another vector.

```lua
local result = myObject:dot(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

??? example "Example: The visualization of vector reflection"

	outDirection = inDirection - (normal * inDirection:dot(normal) * 2)

	```lua
	
	---@type niSwitchNode, niSwitchNode, niCamera
	local lineIn, lineOut, camera
	local verticalOffset = tes3vector3.new(0, 0, -30)
	
	local function onLoaded()
		-- MWSE ships with a mesh which contains a few useful widgets.
		-- These can be used during debugging.
		local mesh = tes3.loadMesh("mwse\\widgets.nif") --[[@as niNode]]
		local widgets = {
			-- 3D coordinate axes
			arrows = mesh:getObjectByName("unitArrows") --[[@as niTriShape]],
			-- A common switch node that has three almost infinite lines
			-- along each coordinate exis
			axes = mesh:getObjectByName("axisLines") --[[@as niSwitchNode]],
			plane = mesh:getObjectByName("unitPlane") --[[@as niTriShape]],
			sphere = mesh:getObjectByName("unitSphere") --[[@as niTriShape]]
		}
	
		local root = tes3.worldController.vfxManager.worldVFXRoot
		---@cast root niNode
	
		lineIn = widgets.axes:clone() --[[@as niSwitchNode]]
		lineOut = lineIn:clone() --[[@as niSwitchNode]]
	
		root:attachChild(lineIn)
		root:attachChild(lineOut)
		root:update()
	
		-- switchIndex = 0 - x axis (red)
		-- switchIndex = 1 - y axis (green)
		-- switchIndex = 2 - z axis (blue)
		lineIn.switchIndex = 1
		lineOut.switchIndex = 1
		camera = tes3.worldController.worldCamera.cameraData.camera
	end
	event.register(tes3.event.loaded, onLoaded)
	
	local function simulateCallback()
		lineIn.translation = tes3.getPlayerEyePosition() + verticalOffset
	
		local inDirection = camera.worldDirection
		local rotation = lineIn.rotation:copy()
		rotation:lookAt(inDirection, camera.worldUp)
	
		lineIn.rotation = rotation
		lineIn:update()
	
		-- Now get the coordinates for the outLine
		--local inDirection = tes3.getPlayerEyeVector()
		local hit = tes3.rayTest({
			position = lineIn.translation,
			direction = inDirection,
			returnNormal = true,
			returnSmoothNormal = true,
			ignore = { tes3.player, tes3.player1stPerson }
		})
		if not hit then return end
	
		lineOut.translation = hit.intersection
	
		local normal = hit.normal
		local outDirection = inDirection - (normal * inDirection:dot(normal) * 2)
		outDirection:normalize()
		local axis = outDirection:cross(inDirection)
		local rotation = tes3matrix33.new()
		rotation:lookAt(outDirection, axis:normalized())
	
		lineOut.rotation = rotation
		lineOut:update()
	end
	event.register(tes3.event.simulate, simulateCallback)

	```

***

### `heightDifference`
<div class="search_terms" style="display: none">heightdifference</div>

Calculates the vertical distance to another vector.

```lua
local result = myObject:heightDifference(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` (number)

***

### `interpolate`
<div class="search_terms" style="display: none">interpolate</div>

Calculates the interpolated position against the target vector using the `distance` parameter.

```lua
local result = myObject:interpolate(targetPoint, distance)
```

**Parameters**:

* `targetPoint` ([tes3vector3](../types/tes3vector3.md))
* `distance` (number)

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `length`
<div class="search_terms" style="display: none">length</div>

Calculates the length of the vector.

```lua
local result = myObject:length()
```

**Returns**:

* `result` (number)

***

### `lerp`
<div class="search_terms" style="display: none">lerp</div>

Calculates the interpolated vector between this vector and another, given a transition.

```lua
local lerpedVector = myObject:lerp(toVector, transition)
```

**Parameters**:

* `toVector` ([tes3vector3](../types/tes3vector3.md)): The vector to interpolate towards.
* `transition` (number): The interpolation value. Must be between `0.0` (closer to this vector) and `1.0` (closer to the other vector).

**Returns**:

* `lerpedVector` ([tes3vector3](../types/tes3vector3.md)): The calculated value.

***

### `max`
<div class="search_terms" style="display: none">max</div>

Returns a vector containing the maximum values for each component of the given vectors.

```lua
local result = myObject:max(other)
```

**Parameters**:

* `other` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `min`
<div class="search_terms" style="display: none">min</div>

Returns a vector containing the minimum values for each component of the given vectors.

```lua
local result = myObject:min(other)
```

**Parameters**:

* `other` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `negate`
<div class="search_terms" style="display: none">negate</div>

Negates all values in the vector.

```lua
myObject:negate()
```

***

### `normalize`
<div class="search_terms" style="display: none">normalize</div>

Normalize the vector in-place, or set its components to zero if normalization is not possible. Returns `true` if the vector was successfully normalized.

```lua
local result = myObject:normalize()
```

**Returns**:

* `result` (boolean)

***

### `normalized`
<div class="search_terms" style="display: none">normalized</div>

Get a normalized copy of the vector.

```lua
local result = myObject:normalized()
```

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `outerProduct`
<div class="search_terms" style="display: none">outerproduct</div>

Calculates the outer product with another vector.

```lua
local result = myObject:outerProduct(vec)
```

**Parameters**:

* `vec` ([tes3vector3](../types/tes3vector3.md))

**Returns**:

* `result` ([tes3matrix33](../types/tes3matrix33.md))

***

### `toColor`
<div class="search_terms" style="display: none">tocolor</div>

Converts the vector to `niColor` object.

```lua
local result = myObject:toColor()
```

**Returns**:

* `result` ([niColor](../types/niColor.md))

***

## Functions

### `new`
<div class="search_terms" style="display: none">new</div>

Creates a new vector. If no parameters are provided, an empty set will be constructed.

```lua
local vector = tes3vector3.new(x, y, z)
```

**Parameters**:

* `x` (number): *Default*: `0`.
* `y` (number): *Default*: `0`.
* `z` (number): *Default*: `0`.

**Returns**:

* `vector` ([tes3vector3](../types/tes3vector3.md))

***

### `ones`
<div class="search_terms" style="display: none">ones</div>

Creates a new vector with all components set to 1.

```lua
local vector = tes3vector3.ones()
```

**Returns**:

* `vector` ([tes3vector3](../types/tes3vector3.md))

***

### `unitX`
<div class="search_terms" style="display: none">unitx</div>

Creates a new vector pointing along the positive X axis.

```lua
local vector = tes3vector3.unitX()
```

**Returns**:

* `vector` ([tes3vector3](../types/tes3vector3.md))

***

### `unitY`
<div class="search_terms" style="display: none">unity</div>

Creates a new vector pointing along the positive Y axis.

```lua
local vector = tes3vector3.unitY()
```

**Returns**:

* `vector` ([tes3vector3](../types/tes3vector3.md))

***

### `unitZ`
<div class="search_terms" style="display: none">unitz</div>

Creates a new vector pointing along the positive Z axis.

```lua
local vector = tes3vector3.unitZ()
```

**Returns**:

* `vector` ([tes3vector3](../types/tes3vector3.md))

***

### `zeroes`
<div class="search_terms" style="display: none">zeroes</div>

Creates a new vector with all components set to 0.

```lua
local vector = tes3vector3.zeroes()
```

**Returns**:

* `vector` ([tes3vector3](../types/tes3vector3.md))

***

## Math Operations

### Addition (`+`)

| Left operand type | Right operand type | Result type | Description |
| ----------------- | ------------------ | ----------- | ----------- |
| [tes3vector3](../types/tes3vector3.md) | number | [tes3vector3](../types/tes3vector3.md) | Add the given number to each of the vector's components. |
| [tes3vector3](../types/tes3vector3.md) | [tes3vector3](../types/tes3vector3.md) | [tes3vector3](../types/tes3vector3.md) | Standard vector addition. |

***

### Division (`/`)

| Left operand type | Right operand type | Result type | Description |
| ----------------- | ------------------ | ----------- | ----------- |
| [tes3vector3](../types/tes3vector3.md) | number | [tes3vector3](../types/tes3vector3.md) | Divides the vector by a scalar. |

***

### Length (`#`)

| Result type | Description |
| ----------- | ----------- |
| number | Evaluates to the vector's length in [game units](https://mwse.github.io/MWSE/references/general/game-units/). |

***

### Multiplication (`*`)

| Left operand type | Right operand type | Result type | Description |
| ----------------- | ------------------ | ----------- | ----------- |
| [tes3vector3](../types/tes3vector3.md) | [tes3vector3](../types/tes3vector3.md) | [tes3vector3](../types/tes3vector3.md) | The per-element multiplication of two vectors, also known as [Hadamard product](https://en.wikipedia.org/wiki/Hadamard_product_(matrices)). |
| [tes3vector3](../types/tes3vector3.md) | number | [tes3vector3](../types/tes3vector3.md) | Multiplies the vector by a scalar. |

***

### Subtraction (`-`)

| Left operand type | Right operand type | Result type | Description |
| ----------------- | ------------------ | ----------- | ----------- |
| [tes3vector3](../types/tes3vector3.md) | number | [tes3vector3](../types/tes3vector3.md) | Subtracts given number from each of the vector's components. |
| [tes3vector3](../types/tes3vector3.md) | [tes3vector3](../types/tes3vector3.md) | [tes3vector3](../types/tes3vector3.md) | Standard vector subtraction. |

***

### Unary minus (`-`)

| Result type | Description |
| ----------- | ----------- |
| [tes3vector3](../types/tes3vector3.md) | Swaps the sign of the vector's components. |

