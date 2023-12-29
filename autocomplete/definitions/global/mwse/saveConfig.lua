return {
	type = "function",
	description = [[Saves a config table to Data Files\\MWSE\\config\\{fileName}.json. The config is converted to JSON during saving.]],
	arguments = {
		{ name = "fileName", type = "string", description = "Usually named after your mod." },
		{ name = "config", type = "table", description = "The config table to save." },
		{ name = "jsonOptions", type = "table", optional = true, description = "Used to optionally pass encoding options to the dkjson encoder." },
	},
}