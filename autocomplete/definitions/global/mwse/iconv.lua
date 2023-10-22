return {
	type = "function",
	description = [[Converts the provided string in UTF8 encoding to Morrowind's codepage base encoding.]],
	arguments = {
		{ name = "languageCode", type = "tes3.languageCode", description = "Determines the language (and appropriate encoding) to use. Maps to values in [`tes3.languageCode`](https://mwse.github.io/MWSE/references/language-codes/) table." },
		{ name = "utf8string", type = "string", description = "The string to convert" },
	},
	returns = { name = "converted", type = "string" }
}