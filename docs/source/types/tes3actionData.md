# tes3actionData
<div class="search_terms" style="display: none">tes3actiondata, actiondata</div>

<!---
	This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
	More information: https://github.com/MWSE/MWSE/tree/master/docs
-->

A substructure of mobile actors that provides information about the current or previous action.

??? example "Example: Active blocking system"

	A simple implementation that allows pressing the ++g++ key to rise shield and block the next enemy attack.

	```lua
	event.register(tes3.event.keyDown, function(e)
		if e.keyCode ~= tes3.scanCode.g then return end
	
		-- Start block anim.
		local animRefr = tes3.mobilePlayer.is3rdPerson and tes3.player1stPerson or tes3.player
		tes3.playAnimation({
			reference = animRefr,
			shield = tes3.animationGroup.shield,
			loopCount = 0
		})
	
		-- Pretend blocking state was triggered.
		-- When set, the controller will clean up the anim after it completes. Resets to 0 after clean up.
		tes3.mobilePlayer.actionData.blockingState = 2
	end)
	
	---@param e attackHitEventData
	event.register(tes3.event.attackHit, function(e)
		local target = e.targetMobile
		if not target then return end
	
		local isBlocking = target.actionData.blockingState > 0
	
		if target.readiedShield and isBlocking then
			-- This blocks hits and redirects damage to the shield.
			-- If there is no shield, it still blocks damage, so check for a shield first.
			e.mobile.actionData.attackWasBlocked = true
		end
	end)

	```

## Properties

### `aiBehaviorState`
<div class="search_terms" style="display: none">aibehaviorstate</div>

The behavior state. This maps to values in [`tes3.aiBehaviorState`](https://mwse.github.io/MWSE/references/ai-behavior-states/) namespace.

**Returns**:

* `result` ([tes3.aiBehaviorState](../references/ai-behavior-states.md))

***

### `aiPackageCount`
<div class="search_terms" style="display: none">aipackagecount</div>

The number of AI packages available.

**Returns**:

* `result` (number)

***

### `animationAttackState`
<div class="search_terms" style="display: none">animationattackstate</div>

The actor's animation state. Maps to values in [`tes3.animationState`](https://mwse.github.io/MWSE/references/animation-states/) namespace.

**Returns**:

* `result` ([tes3.animationState](../references/animation-states.md))

***

### `animGroupBlocking`
<div class="search_terms" style="display: none">animgroupblocking</div>

The animation group when blocking.

**Returns**:

* `result` (number)

***

### `animGroupCurrentAction`
<div class="search_terms" style="display: none">animgroupcurrentaction</div>

The animation group for the current action.

**Returns**:

* `result` (number)

***

### `animGroupStunEffect`
<div class="search_terms" style="display: none">animgroupstuneffect</div>

The animation group for when stunned.

**Returns**:

* `result` (number)

***

### `animSectionCurrentAction`
<div class="search_terms" style="display: none">animsectioncurrentaction</div>

The animation section for the current action.

**Returns**:

* `result` (number)

***

### `attackSwing`
<div class="search_terms" style="display: none">attackswing</div>

When attacking, this value represents how much the weapon has been pulled back. The value ranges from [0.0 - 1.0].

**Returns**:

* `result` (number)

***

### `attackWasBlocked`
<div class="search_terms" style="display: none">attackwasblocked</div>

A flag that indicates if an attack failed its block check on the initial attack swing, and should be blocked if it connects. May be modified before the strike hits to cause the attack to be blocked. This flag negates damage even if no shield is equipped, so you should check if a shield is present before setting it.

**Returns**:

* `result` (boolean)

***

### `blockingState`
<div class="search_terms" style="display: none">blockingstate</div>

A state index that indicates an actor's blocking state. It is zero when not blocking and non-zero when blocking. A value of 1 indicates a state transition from non-blocking to blocking, while a value of 2 means blocking is active (where the block animation is currently playing and should not be interrupted). The action simulation will reset the value to 0 at the end of a block animation.

**Returns**:

* `result` (number)

***

### `currentAnimationGroup`
<div class="search_terms" style="display: none">currentanimationgroup</div>

Actor's current animation group. Maps to values in [`tes3.animationGroup`](https://mwse.github.io/MWSE/references/animation-groups/) namespace.

**Returns**:

* `result` ([tes3.animationGroup](../references/animation-groups.md))

***

### `dispositionCombatChange`
<div class="search_terms" style="display: none">dispositioncombatchange</div>

The disposition modifier for combat.

**Returns**:

* `result` (number)

***

### `fightCombatChange`
<div class="search_terms" style="display: none">fightcombatchange</div>

The fight modifier for combat.

**Returns**:

* `result` (number)

***

### `hitTarget`
<div class="search_terms" style="display: none">hittarget</div>

The actor's attack target. The target will be saved in `hitTarget` field until a new attack is made. Missing an attack will clear `hitTarget` field.

**Returns**:

* `result` ([tes3mobileActor](../types/tes3mobileActor.md), nil)

***

### `lastBarterHoursPassed`
<div class="search_terms" style="display: none">lastbarterhourspassed</div>

A 16-bit hourstamp of the last time a merchant's barter gold was at its base level. It is used as a timer for resetting barter gold, which happens on interacting with a merchant at hourstamp `lastBarterHoursPassed + GMST fBarterGoldResetDelay` or later. Barter gold can also reset when a mobile expires.

**Returns**:

* `result` (number)

***

### `lastPositionBeforeCombat`
<div class="search_terms" style="display: none">lastpositionbeforecombat</div>

When an actor enters combat, the last position is stored here so that they can navigate back after combat.

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

***

### `lastWitnessedCrimeTimestamp`
<div class="search_terms" style="display: none">lastwitnessedcrimetimestamp</div>

The game timestamp for when the mobile last witnessed a crime.

**Returns**:

* `result` (number)

***

### `nockedProjectile`
<div class="search_terms" style="display: none">nockedprojectile</div>

The currently nocked projectile the associated actor is using. It is available while charging a projectile attack, before releasing the projectile. This can be modified, but can only be set to nil, which will remove the projectile without consuming ammo.

**Returns**:

* `result` ([tes3mobileProjectile](../types/tes3mobileProjectile.md))

***

### `physicalAttackType`
<div class="search_terms" style="display: none">physicalattacktype</div>

A number from the [`tes3.physicalAttackType`](https://mwse.github.io/MWSE/references/physical-attack-types/) enumeration identifying the physical attack type. Can be `tes3.physicalAttackType.slash`, `.chop`, `.thrust`, `.projectile`, `.creature1`, `.creature2`, or `.creature3.`

Proper time to change the attack direction is the [attackStart](https://mwse.github.io/MWSE/events/attackStart/) event. See the example below to see how.

**Returns**:

* `result` ([tes3.physicalAttackType](../references/physical-attack-types.md))

??? example "Example: Changing axe attack direction"

	```lua
	
	-- In this example, we force the attack
	-- direction for axes to always be chop
	
	---@param e attackStartEventData
	local function onAttackStart(e)
		local mobile = e.reference.mobile
		if not mobile then return end
	
		local weapon = mobile.readiedWeapon.object --[[@as tes3weapon]]
	
		if weapon.type == tes3.weaponType.axeOneHand
		or weapon.type == tes3.weaponType.axeTwoHand then
			-- Now actually change the attack direction
			e.attackType = tes3.physicalAttackType.chop
		end
	end
	
	event.register(tes3.event.attackStart, onAttackStart)

	```

***

### `physicalDamage`
<div class="search_terms" style="display: none">physicaldamage</div>

When attacking, this is the value of the weapon damage that was rolled. This value takes into account the actor's strength, attack swing and weapon condition, but it doesn't include difficulty nor target's armor. This value is updated on an attack. After the attack this value will still contain the damage rolled. It will be refreshed on a new attack.

**Returns**:

* `result` (number)

***

### `quantizedHitAngleX`
<div class="search_terms" style="display: none">quantizedhitanglex</div>

The last hit angle.

**Returns**:

* `result` (number)

***

### `quantizedHitAngleY`
<div class="search_terms" style="display: none">quantizedhitangley</div>

The last hit angle.

**Returns**:

* `result` (number)

***

### `quantizedHitAngleZ`
<div class="search_terms" style="display: none">quantizedhitanglez</div>

The last hit angle.

**Returns**:

* `result` (number)

***

### `rescaledFacingBeforeCombat`
<div class="search_terms" style="display: none">rescaledfacingbeforecombat</div>

The last facing used before combat.

**Returns**:

* `result` (number)

***

### `stolenFrom`
<div class="search_terms" style="display: none">stolenfrom</div>

No description yet available.

**Returns**:

* `result` ([tes3object](../types/tes3object.md))

***

### `target`
<div class="search_terms" style="display: none">target</div>

The actor's attack target, stored until the actor attacks successfully again. In contrast to `hitTarget`, `target` property isn't cleared on missed attack.

**Returns**:

* `result` ([tes3mobileActor](../types/tes3mobileActor.md), nil)

***

### `walkDestination`
<div class="search_terms" style="display: none">walkdestination</div>

If moving to a location, this is the position to be walked to.

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md))

