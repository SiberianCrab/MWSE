return {
	type = "event",
	description = "The `musicChangeTrack` event when the game is changing to play a new piece of music.",
	blockable = true,
	related = { "musicSelectTrack" },
	eventData = {
		["situation"] = {
			type = "tes3.musicSituation",
			readOnly = true,
			description = "Maps to [`tes3.musicSituation`](https://mwse.github.io/MWSE/references/music-situations/), indicating combat, non-combat, or scripted music.",
		},
		["context"] = {
			type = "string",
			readOnly = true,
			description = "A short lowercase string that describes why the music is being played, to give more context. `explore` and `combat` values mean the game has chosen a new background music to play. `title` will play (and loop) on the main menu. `level` will play whenever the player has rested and is ready to level up. `mwscript` means a script has used the `StreamMusic` mwscript command. `death` means the player has died. `lua` means that a lua script has requested new music.",
		},
		["music"] = {
			type = "string",
			description = "The track that will be played. This can be changed to a new path, but it must be valid. Note that unlike the `musicSelectTrack` event, this value is not relative to `Data Files\\music`.",
		},
		["volume"] = {
			type = "number",
			description = "The volume of the track to be played, ranging from `0.0` to `1.0`. This can be modified.",
		},
		["crossfade"] = {
			type = "number",
			description = "The number of milliseconds of crossfade that will be used to blend the current music to the new music.",
		},
	},
}
