return {
	type = "function",
	deprecated = true,
	description = [[Fetches the core game object that represents a game setting. While this function accepts a name, it is recommended to use the [`tes3.GMST`](https://mwse.github.io/MWSE/references/gmst/) constants.]],
	arguments = {
		{ name = "id", type = "tes3.gmst|string" },
	},
	returns = "gameSetting",
	valuetype = "tes3gameSetting",
}
