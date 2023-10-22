return {
	type = "event",
	description = "The musicSelectTrack event occurs when new music is needed after a playing music track ends, or the combat situation changes. It allows you to select your own music for the current conditions by setting eventData.music. The event can be blocked, which prevents a new explore or battle track from being chosen randomly. Blocking only works if `eventData.music` is not set.",
	blockable = true,
	related = { "musicChangeTrack" },
	eventData = {
		["situation"] = {
			type = "tes3.musicSituation",
			readOnly = true,
			description = "Maps to [`tes3.musicSituation`](https://mwse.github.io/MWSE/references/music-situations/), indicating combat or non-combat music.",
		},
		["music"] = {
			type = "string",
			optional = true,
			description = "If set to the path of a given track (relative to Data Files/music), it will play the given path instead of a random one.",
		},
	},
}
