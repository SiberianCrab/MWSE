--- @meta

-- This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
-- More information: https://github.com/MWSE/MWSE/tree/master/docs

--- Works in conjuction with mobile AI to perform idle, movement, and attack animations. Holds data on the status of the current and next desired animation states for the different body sections that can be animated.
--- @class tes3playerAnimationController : tes3actorAnimationController
--- @field allowVerticalAirControl boolean Controls if additional vertical movement is possible while jumping or falling, by looking up and down and moving forward in the air. It is unphysical and not used by any normal gameplay mechanic. It is independent of flying movement.
--- @field cameraOffset tes3vector3 Additional offset applied to the camera's position in the third person view. It may be overridden by MGE.
--- @field firstPersonHeadCameraNode niCamera *Read-only*. This is the camera used while in first person. Switching from first person to third person point of view doesn't affect this camera.
--- @field is3rdPerson boolean *Read-only*. This flag is set to `true` when the player's view is in third person. To change the player's POV, you can use [tes3.force1stPerson](https://mwse.github.io/MWSE/apis/tes3/#tes3force1stperson) and [tes3.force3rdPerson](https://mwse.github.io/MWSE/apis/tes3/#tes3force3rdperson).
--- @field pickData niPick *Read-only*. 
--- @field shadowCameraMatrix tes3matrix33 *Read-only*. The local rotation matrix of the shadow camera.
--- @field switchPOVMode integer This property is briefly set to `1` (doesn't switch when incapacitated) or `2` (always switch) for one frame to change the point of view. You should prefer to use [tes3.force1stPerson](https://mwse.github.io/MWSE/apis/tes3/#tes3force1stperson) and [tes3.force3rdPerson](https://mwse.github.io/MWSE/apis/tes3/#tes3force3rdperson).
--- @field useThirdPersonAfterVanityCameraDone boolean This flag is set to `true` if vanity mode was entered from third person view. If vanity mode was entered from first person view, this flag is set to `false`.
--- @field vanityCamera niCamera *Read-only*. The vanity camera scene node.
--- @field vanityCameraAngle number The current heading of the orbiting vanity camera, in radians. An angle of 0 places the camera to the north of the player.
--- @field vanityCameraDistance integer The orbiting radius of the camera during vanity mode in [game units](https://mwse.github.io/MWSE/references/general/game-units/). Measured from the center of the player's head.
--- @field vanityCameraEnabled integer The value of this property is `1` during vanity camera mode, and `0` otherwise.
--- @field vanityCameraZ number The offset on up-down (world z) axis of the camera in third person or during vanity mode from the player's head height in [game units](https://mwse.github.io/MWSE/references/general/game-units/).
