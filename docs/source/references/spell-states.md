---
hide:
  - toc
---

# Spell States

!!! tip
	These values are available in Lua by their index in the `tes3.spellState` table. For example, `tes3.spellState.retired` has a value of `7`.

Index          | Value | Description
-------------- | ----- | -----------------------------------
preCast        | `0`   | Has not been cast yet
cast           | `1`   | Has just been casted
beginning      | `4`   | Has just been applied to a target
working        | `5`   | Is applying its effects each frame
ending         | `6`   | Is ending and being cleaned up. For magic effects that modify stats, during `ending` state, the corresponding stat will be restored if the effect has `negateOnExpiry = true`. For "damage over time" effects, the damage won't be applied anymore during `ending` state.
retired        | `7`   | Has ended and will be deleted
workingFortify | `8`   | Same as working for fortify effects
endingFortify  | `9`   | Same as ending for fortify effects
