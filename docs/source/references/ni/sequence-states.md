---
hide:
  - toc
---

# Sequence States

!!! tip
	These values are available in Lua by their index in the `ni.sequenceState` table. For example, `ni.sequenceState.animating` has a value of `1`.

Index        | Value  | Description
------------ | ------ | ------------------------
inactive     | `0`    | The sequence isn't playing currently.
animating    | `1`    | The sequence is active.
layerBlend   | `2`    |
syncSeqBlend | `3`    |
blendSource  | `4`    | The sequence is the source animation used in a blending transition.
blendDest    | `5`    | The sequence is the destination animation used in a blending transition.
morphSource  | `6`    | The sequence is the source animation used in a morph transition.
morphDest    | `7`    | The sequence is the destination animation used in a morph transition.
sumSource    | `8`    | The sequence is the source animation used in a sum transition.
sumDest      | `9`    | The sequence is the destination animation used in a sum transition.
