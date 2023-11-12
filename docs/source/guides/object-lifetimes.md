# Object Lifetimes

## Introduction

Lua objects have lifetimes. An object's lifetime starts at the object creation, while its lifetime ends when it goes out of scope. A similar concept applies to the objects in the Morrowind engine. Since objects in the Morrowind engine are constructed in the code external to Lua, those objects can be deconstructed while the Lua holds reference variables to them, rendering the Lua reference variables invalid. For example, the [`e.reference`](../events/itemDropped.md#event-data) (of `tes3reference` type) in the [itemDropped](../events/itemDropped.md) event is only valid during the very same event. The player may pick up the item, and the `e.reference` will be gone, it's destructed in the Morrowind engine. This kind of Lua reference variables are called *dangling references*. Since *dangling references* refer to variables that no longer exist, using them leads to script errors and may crash the game. Thus, understanding how the lifetimes of Morrowind objects exposed to Lua work will help writing scripts free of these kinds of issues.

As a general rule, `tes3reference`s will be valid for the lifetime of the event you can get them from. After the event, the inventory items may be gone, actors may deactivate after changing cells, and magic expires when leaving a cell.

### Lua reference variables

The term Lua reference variables used in this guide denotes a reference variable in programmer's sense of word: a variable that refers to the value of another variable. The concept is the same as reference variables in C or C++. Here we provide an example of Lua reference variables:

```lua linenums="1"
-- Let's create a table and store it in the variable foo.
local foo = { a = "apple" }

-- Now, let's create a reference to the variable foo.
local bar = foo

-- Let's see what we've got
print(foo.a) --> apple
print(bar.a) --> apple

-- Modifiying foo will also change all the reference variables since they all refere to the same memory.
foo.b = "orange"

print(foo.b) --> orange
print(bar.b) --> orange

-- The same applies when changing bar.
bar.a = "banana"
print(foo.a) --> banana
print(bar.a) --> banana
```

It's important to differentiate the concept of Lua reference variables from the [`tes3reference`](../types/tes3reference.md) objects. The `tes3reference` is a name for an object type in the Morrowind engine.

### Lifetimes of Lua variables

```lua linenums="1"

-- The upper-most scope. The variable lifetime is until the end of the program (Morrowind) execution
local someNum = 4

local function foo(param)
	-- The lifetime of the param lasts only during the execution of foo()
end

do
	local someStr = "hello"
	-- someStr only exists during the execution of this do-end block
end
```

### The problem

MWSE exposes various objects in the Morrowind engine as Lua reference variables. The parent code in the Morrowind engine determines when the object lifetime ends. Any Lua reference variables refering to those objects may become invalid at any time (*dangling references*). Accessing a destructed Morrowind object through a Lua reference variable leads to crashes. Such cases are usually encountered when caching reference variables refering Morrowind objects in timer callbacks. Consider the following example:

```lua linenums="1" hl_lines="5-7 10-12"
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

	-- Creating a Lua reference variable that refers to the object in the `e.reference`.
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

Now, let's analyze what happens. The highlighted early-outs filter out the cases of `damaged` event that we don't want our code to execute for. During the `ref = e.reference` assignment, we created a Lua reference variable that refers to an object in the Morrowind engine. Note that the `e.reference` in itself is a Lua reference variable to the same Morrowind object. Using the `ref` object is perfectly fine within the `onDamaged` function. The problems arise when using asynchronous code facilities such as `timer` API. The `timer.start` function registers a `callback` function to execute after the `duration` time has passed. During that time the Morrowind object our `ref` variable refers to may have been destroyed, and we could be using a **dangling reference** in our `callback` function.

## Safe object handles

MWSE provides `mwseSafeObjectHandle` class to handle such cases. When you need to use a Lua reference variable that refers to a Morrowind object inside a timer `callback`, just construct a safe handle for it. Now, let's use it in our previous example:

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

	-- Creating a Lua reference variable that refers to the object in the `e.reference`.
	local ref = e.reference

	-- Now, crate a safe handle for the object.
	local handle = tes3.makeSafeObjectHandle(ref)
	timer.start({
		type = timer.simulate,
		duration = 1,
		iterations = 3,
		callback = function()
			-- Before using our object, check if it is still valid,
			-- if not, make an early-out
			if not handle:valid() then
				return
			end
			-- To get our object back from safe handle use `getObject` method.
			local ref = handle:getObject()
			local mob = ref.mobile --[[@as tes3mobileActor|nil]]
			-- The `mobile` may not exist on a tes3reference at all times.
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

Before describing the lifetimes of Morrowind objects of individual classes, it's desirable to understand the differences between objects, references (`tes3reference`s this time), and mobiles in the Morroiwind engine.

A base object, inheriting from the tes3baseObject class, is an object of certain type usually created in the Construction Set's Object Window. Those are: tes3armor, tes3spell, tes3static, tes3creature, etc. When an object is dragged to the Render Window, a reference (`tes3reference`) is created. The `tes3reference` structure holds the data for an object placed in certain cell in the game world. Those are position, rotation, scale, and optionally, some additional data in the [attachments](../types/tes3reference.md#attachments) field. The reference data can be inspected in the CS by double-clicking on any placed reference in the Render Window. There may be zero, one or more `tes3reference`s of a base object placed in the game world. In addition, there is a `tes3mobileObject` class for current velocity and actor's AI-related data. It exists for actors (player, NPCs, creatures) and projectiles (arrows, bolts, spell projectiles) inside the AI processing range.

Another point to keep in mind: certain object types that have inventories, such as tes3container, tes3creature, and tes3npc have corresponding instances (tes3containerInstance, tes3creatureInstance, tes3npcInstance). The `tes3reference`s in unvisited cells point to the base objects that have the IDs defined in the CS, for example: `"mudcrab"`. Once cloned, those `tes3reference`s point to the appropriate object instances, and the `tes3reference` IDs have the ref number appended to the base object ID. For example, `"mudcrab00000008"` is the reference ID of the eighth encountered mudcrab in the playthrough. Cloning ensures that the changes (inventory changes for actors and containers, and stat changes for actors) to the object instance don't affect all the other objects. During cloning, item leveled lists in the object's inventory are resolved.

### Lifetimes of Objects, References and Mobiles

Base object lifetime is during the whole execution of the program (Morrowind), meaning variables that Lua reference variables refering to the base objects (tes3alchemy, tes3container, etc.) can be used at any time in Lua scripts.

The `tes3reference`s are tied to the cell they were placed (in the Construction Set or by a Lua script) or walked to in the case of actors during the current play session. There are two types of `tes3referenece`s: temporary and [persistent](../types/tes3reference.md#persistent). The Construction Set makes each `tes3reference` temporary by default. Temporary `tes3reference`s' lifetime ends when the Morrowind engine clears the active cell cache. A `tes3reference` can be made persistent in the Construction Set by double clicking at the placed reference in the Render Window and checking the "Reference Persist" checkbox. In addition, the Construction Set always marks NPC references as persistent `tes3reference`s. Persistent `tes3reference`'s lifetime is during the whole execution of the program (Morrowind). When manipulating `tes3reference` objects in timer callbacks `mwseSafeObjectHandle`s should be used, because of temporary `tes3reference`s.

The mobile actor (`tes3mobileCreature` and `tes3mobileNPC`) structures are created on actors when the player enters their cell, on summoned, teleported actors and on certain script commands that reset actor state such as resurrection and werewolf transformation. The lifetime of mobile actor structures expires in 72 in-game hours after the cell they are in wasn't visited. The mobile projectile structures (`tes3mobileProjectile` and `tes3mobileSpellProjectile`) expire when they collide with something or when the player leaves the cell.
