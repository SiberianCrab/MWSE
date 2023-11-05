# Object Lifetimes

## Introduction

Lua objects have lifetimes. An object's lifetime starts at the object's creation, while its lifetime ends when it goes out of scope.

```lua linenums="1"

-- The upper-most scope. This variable's lifetime is until the end of the program (Morrowind) execution
local someNum = 4

local function foo(param)
	-- The lifetime of the param lasts only during the execution of foo()
end

do
	local someStr = "hello"
	-- someStr only exists during the execution of this do-end block
end
```

MWSE exposes various objects in the Morrowind engine as references. The parent code in the Morrowind engine determines when the object's lifetime ends. Any references on the Lua side to those objects may become invalid at any time. Accessing an object in the Morrowind engine through a Lua reference will often lead to crashes. Such cases are usually encountered when caching references to Morrowind objects and using timers. Consider the following example:

```lua linenums="1"
---@param e damagedEventData
local function onDamaged(e)
	-- Let's implement additional damage over time for fire damage

	if e.source ~= tes3.damageSource.magic then
		return
	end
	local effect = e.activeMagicEffect
	-- Early-out if the damage doesn't come from fire damage magic effect
	if not effect or effect.id ~= tes3.effect.fireDamage then
		return
	end

	local damage = e.damage / 10

	-- Creating a reference (in the programmer's sense of the word)
	-- to the object stored in the e.reference field.
	local ref = e.reference

	-- Now, let's try to apply the damage using a timer:
	timer.start({
		type = timer.simulate,
		duration = 1,
		iterations = 3,
		callback = function()
			-- Ouch! This may crash if the `ref` was deconstructed in the engine.
			local mobile = ref.mobile
			mobile:applyDamage({
				damage = damage,
				resistAttribute = tes3.effectAttribute.resistFire
			})
		end
	})
end
event.register(tes3.event.damaged, onDamaged)
```

Now, let's analyze what happens. The early-outs filter out the cases of `damaged` event that we don't want our code to execute for. During the `ref = e.reference` assignment, we created a reference to an object in the Morrowind engine. Note that the `e.reference` in itself is a reference to the same object. Using the `ref` object is perfectly fine within the `onDamaged` function. The problems arise when using asynchronous code facilities such as `timer` API. The `timer.start` function registers a `callback` function to execute after the `duration` time has passed. During that time the object our `ref` variable references may have been destroyed, and our `callback` function could be a dangling reference.

## Safe object handles

MWSE provides `mwseSafeObjectHandle` class to handle such cases. When you need to use an object inside a timer `callback` just construct a safe handle for it. Now, let's use it in our previous example:

```lua linenums="1"
---@param e damagedEventData
local function onDamaged(e)
	-- Let's implement additional damage over time for fire damage

	if e.source ~= tes3.damageSource.magic then
		return
	end
	local effect = e.activeMagicEffect
	-- Early-out if the damage doesn't come from fire damage magic effect
	if not effect or effect.id ~= tes3.effect.fireDamage then
		return
	end

	local damage = e.damage / 10

	-- Creating a reference (in programming sense of word) to the object stored in the e.reference field.
	local ref = e.reference

	-- Now, crate a safe handle for the object.
	local handle = tes3.makeSafeObjectHandle(ref)
	timer.start({
		type = timer.simulate,
		duration = 1,
		iterations = 3,
		callback = function()
			-- Before using our object, check if it is still valid,
			-- if not make an early-out
			if not handle:valid() then
				return
			end
			-- To get our object back from safe handle use `getObject` method.
			local ref = handle:getObject()
			local mob = ref.mobile --[[@as tes3mobileActor|nil]]
			-- The `mobile` may not exist on a tes3reference for similar reasons as described above.
			if not mob then
				return
			end
			-- Now we can safely use our `mob` object.
			local damageDone = mob:applyDamage({
				damage = damage,
				resistAttribute = tes3.effectAttribute.resistFire
			})
			tes3.messageBox("Additional damage = %.2f", damageDone)
		end,
	})
end
event.register(tes3.event.damaged, onDamaged)
```

## Lifetimes of Individual Objects

### Definition of Objects, References and Mobiles

Before describing the lifetimes of objects of individual classes, it's desirable to understand the differences between objects, references, and mobiles.

A base object, inheriting from tes3baseObject class (tes3armor, tes3spell, tes3static, tes3creature...), is an object of certain type usually created in the Construction Set's Object Window. When an object is dragged to the Render Window, a reference (tes3reference) is created. The reference structure holds the data for an object placed in the game world. Those are position, rotation, scale, and optionally, some additional data in the attachments field. The reference data can be inspected in the CS by double-clicking on the reference in the Render Window. One base object may have zero, one, or more references. Think of mudcrabs for example. In addition, there is a `tes3mobileObject` class for current velocity and actor's AI-related data. It exists for actors (player, NPCs, creatures) and projectiles (arrows, bolts, spell projectiles) inside the AI processing range.

Another point to keep in mind: certain object types that have inventories: tes3container, tes3creature, and tes3npc have corresponding instances (tes3containerInstance, tes3creatureInstance, tes3npcInstance). The references in unvisited cells point to the base objects that have the ids defined in the CS, for example: `"mudcrab"`. Once cloned, those references point to the appropriate object instances, and the reference IDs have the ref number appended to the base object id. For example, `"mudcrab00000008"` is the reference ID of the eighth encountered mudcrab in the playthrough. Cloning ensures that the changes (inventory changes for actors and containers and stat changes for actors...) to the object instance don't affect all the other objects. During cloning, item leveled lists in the object's inventory are resolved.

### Lifetimes of Objects, References and Mobiles

Base object lifetime is during the whole execution of the program (Morrowind), meaning variables that reference base objects (tes3alchemy, tes3container, etc.) can be used at any time in Lua scripts.

The references (`tes3reference` objects) are tied to the cell they were placed, e.g. in the Construction Set, or walked to in the case of actors during the current play session. The reference objects exist for 72 in-game hours after their containing cell is unloaded. When manipulating `tes3reference` objects in timer callbacks `mwseSafeObjectHandle`s should be used.

<!---
	TODO: describe the lifetime of mobile objects/actors
-->