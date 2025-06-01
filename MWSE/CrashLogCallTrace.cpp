#include "CrashLogger.hpp"
#include "CrashLogExceptionHandler.hpp"

#include "StringUtil.h"

namespace CrashLogger::Version {
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
#ifdef APPVEYOR_BUILD_NUMBER
			output << fmt::format("Appveyor Build: {}\n", APPVEYOR_BUILD_NUMBER);
#else
			output << "Appveyor Build: <unavailable>\n";
#endif
			output << fmt::format("Build Date: {}\n", MWSE_BUILD_DATE);
		}
		catch (...) {
			output << "Failed to log version." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Playtime {
	std::stringstream output;

	std::chrono::time_point<std::chrono::system_clock> gameStart;

	extern void Init() {
		gameStart = std::chrono::system_clock::now();
	}

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			const auto gameEnd = std::chrono::system_clock::now();
			const auto playtime = gameEnd - gameStart;
			output << fmt::format("Playtime: {:%H:%M:%S}\n", playtime);
		}
		catch (...) {
			output << "Failed to process playtime." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Exception {
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			const auto exceptionAsString = GetExceptionAsString(info->ExceptionRecord->ExceptionCode);
			output << fmt::format("Exception: {} ({:08X})\n", exceptionAsString, info->ExceptionRecord->ExceptionCode);

			const auto lastError = GetLastError();
			if (lastError) {
				const auto asString = SanitizeString(GetErrorAsString(lastError));
				output << fmt::format("Last Error: {} ({:08X})\n", asString, lastError);
			}
		}
		catch (...) {
			output << "Failed to log exception." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Thread {
	std::stringstream output;

	static std::wstring GetCurrentThreadDescription() {
		wchar_t* pThreadName = nullptr;
		const auto hr = GetThreadDescription(GetCurrentThread(), &pThreadName);
		if (!SUCCEEDED(hr)) {
			return L"<unknown thread>";
		}
		const std::wstring name = pThreadName;
		LocalFree(pThreadName);
		return name;
	}

	static std::string GetThreadName() {
		return mwse::string::from_wstring(GetCurrentThreadDescription());
	}

	extern void Process(EXCEPTION_POINTERS* info) {
		try { output << "Thread: " << GetThreadName() << '\n'; }
		catch (...) { output << "Failed to log thread name." << '\n'; }
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Install {
	std::stringstream output;

	std::filesystem::path getInstallPath() {
		CHAR path[MAX_PATH] = {};
		if (GetModuleFileNameA(NULL, path, MAX_PATH) <= 0) {
			return {};
		}
		return std::filesystem::canonical(path).parent_path();
	}

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			output << fmt::format("Install Path: {}\n", getInstallPath().string());
		}
		catch (...) {
			output << "Failed to log version." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Calltrace {
	std::stringstream output;

	std::string GetCalltraceFunction(UINT32 eip, UINT32 ebp, HANDLE process) {
		/*if (GetModuleFileName((HMODULE)frame.AddrPC.Offset, path, MAX_PATH)) {  //Do this work on non base addresses even on  Windows? Cal directly the LDR function?
		if (!SymLoadModule(process, NULL, path, NULL, 0, 0)) Log() << FormatString("Porcoddio %0X", GetLastError());
		}*/

		const auto moduleBase = PDB::GetModuleBase(eip, process);

		std::string begin = fmt::format("0x{:08X} | ", ebp);

		std::string middle;

		const auto moduleOffset = (moduleBase != 0x00400000) ? eip - moduleBase + 0x10000000 : eip;

		if (const auto module = PDB::GetModule(eip, process); module.empty())
			middle = fmt::format("{:>28s} (0x{:08X}) | {:<40s} |", "???", moduleOffset, "(Corrupt stack or heap?)");
		else if (const auto symbol = PDB::GetSymbol(eip, process); symbol.empty())
			middle = fmt::format("{:>28s} (0x{:08X}) | {:<40s} |", module, moduleOffset, "");
		else
			middle = fmt::format("{:>28s} (0x{:08X}) | {:<40s} |", module, moduleOffset, symbol);

		std::string end;

		if (const auto line = PDB::GetLine(eip, process); !line.empty()) {
			end = " " + line;
		}

		return begin + middle + end;
	}

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			HANDLE process = GetCurrentProcess();
			HANDLE thread = GetCurrentThread();

			DWORD machine = IMAGE_FILE_MACHINE_I386;
			CONTEXT context = {};
			memcpy(&context, info->ContextRecord, sizeof(CONTEXT));

			SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS);

			char workingDirectory[MAX_PATH];
			char symbolPath[MAX_PATH];
			char altSymbolPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, workingDirectory);
			GetEnvironmentVariable("_NT_SYMBOL_PATH", symbolPath, MAX_PATH);
			GetEnvironmentVariable("_NT_ALTERNATE_SYMBOL_PATH ", altSymbolPath, MAX_PATH);
			std::string lookPath = fmt::format("{};{}\\Data\\OBSE\\plugins;{};{}", workingDirectory, workingDirectory, symbolPath, altSymbolPath);

			//	SymSetExtendedOption((IMAGEHLP_EXTENDED_OPTIONS)SYMOPT_EX_WINE_NATIVE_MODULES, TRUE);
			if (!SymInitialize(process, lookPath.c_str(), true)) {
				output << "Error initializing symbol store" << '\n';
			}

			//	SymSetExtendedOption((IMAGEHLP_EXTENDED_OPTIONS)SYMOPT_EX_WINE_NATIVE_MODULES, TRUE);

			STACKFRAME frame = {};
			frame.AddrPC.Offset = info->ContextRecord->Eip;
			frame.AddrPC.Mode = AddrModeFlat;
			frame.AddrFrame.Offset = info->ContextRecord->Ebp;
			frame.AddrFrame.Mode = AddrModeFlat;
			frame.AddrStack.Offset = info->ContextRecord->Esp;
			frame.AddrStack.Mode = AddrModeFlat;
			DWORD eip = 0;

			// crutch to try to copy dbghelp before.
			output << fmt::format("{:^10} |  {:^40} | {:^40} | Source", "ebp", "Function Address", "Function Name") << '\n';

			while (StackWalk(machine, process, thread, &frame, &context, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL)) {
				/*
				Using  a PDB for OBSE from VS2019 is causing the frame to repeat, but apparently only if WINEDEBUG=+dbghelp isn't setted. Is this a wine issue?
				When this happen winedbg show only the first line (this happens with the first frame only probably, even if there are more frames shown when using WINEDEBUG=+dbghelp )
				*/
				if (frame.AddrPC.Offset == eip) break;
				eip = frame.AddrPC.Offset;
				output << GetCalltraceFunction(frame.AddrPC.Offset, frame.AddrFrame.Offset, process) << '\n';
			}
		}
		catch (...) {
			output << "Failed to log callstack." << '\n';
		}
	}

	extern std::stringstream& Get() { output.flush(); return output; }
}

namespace CrashLogger::LuaTraceback {
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			output << mwse::lua::getStackTrace(true) << '\n';
		}
		catch (...) {
			output << "Failed to process lua traceback." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Mods {
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			const auto dataHandler = TES3::DataHandler::get();
			if (dataHandler == nullptr) return;
			const auto activeMods = dataHandler->nonDynamicData->getActiveMods();

			// Get the longest filename column length.
			const auto gameFileWithLongestFilename = *std::max_element(activeMods.begin(), activeMods.end(), [](const auto& a, const auto& b) {
				return std::strlen(a->getFilename()) < std::strlen(b->getFilename());
			});
			const auto gameFileWithLongestAuthor = *std::max_element(activeMods.begin(), activeMods.end(), [](const auto& a, const auto& b) {
				return std::strlen(a->getFilename()) < std::strlen(b->getFilename());
			});
			const auto filenameLength = std::strlen(gameFileWithLongestFilename->getFilename());
			const auto authorLength = std::strlen(gameFileWithLongestAuthor->getAuthor());

			output << fmt::format("{:<{}} | {:<{}} | {:<s}", "File", filenameLength, "Author", authorLength, "Size") << '\n';
			for (const auto gameFile : activeMods) {
				if (!gameFile) break;
				const auto filename = gameFile->getFilename();
				const auto author = gameFile->getAuthor();
				const auto size = gameFile->getFileSize();
				output << fmt::format("{:<{}} | {:<{}} | {} bytes\n", filename, filenameLength, author, authorLength, size);
			}
		}
		catch (...) {
			output << "Failed to process mods." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::LuaMods {
	std::stringstream output;

	struct LuaModResult {
		std::string key;
		std::string firstAuthor;
		std::string version;
	};

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			const auto stateHandle = mwse::lua::LuaManager::getInstance().getThreadSafeStateHandle();
			const auto& lua = stateHandle.state;
			sol::table luaMWSE = lua["mwse"];
			sol::table luaRuntimes = luaMWSE["runtimes"];

			std::vector<LuaModResult> results;

			// Gather our lua mod information.
			for (auto i = 1; i <= luaRuntimes.size(); ++i) {
				sol::table runtime = luaRuntimes[i];

				// We can ignore core mods.
				const auto core_mod = runtime.get_or("core_mod", false);
				if (core_mod) continue;

				sol::optional<std::string> key = runtime["key"];
				sol::optional<std::string> name = runtime["metadata"]["package"]["name"];
				sol::optional<std::vector<std::string>> authors = runtime["metadata"]["package"]["authors"];
				sol::optional<std::string> version = runtime["metadata"]["package"]["version"];

				if (authors && authors.value().size() > 5) {
					authors.value().resize(5);
				}

				results.push_back({
					name ? fmt::format("{} ({})", name.value(), key.value_or("<invalid>")) : key.value_or("<invalid>"),
					authors ? fmt::format("{}", fmt::join(authors.value(), ", ")) : "",
					version.value_or(""),
				});
			}

			// Calculate column widths.
			const auto keyLength = std::max_element(results.begin(), results.end(), [](const auto& a, const auto& b) {
				return a.key.length() < b.key.length();
			})->key.length();
			const auto authorLength = std::max_element(results.begin(), results.end(), [](const auto& a, const auto& b) {
				return a.firstAuthor.length() < b.firstAuthor.length();
			})->firstAuthor.length();

			// We can finally print our table.
			output << fmt::format("{:<{}} | {:<{}} | {:<s}", "Mod", keyLength, "Author", authorLength, "Version") << '\n';
			for (const auto& mod : results) {
				output << fmt::format("{:<{}} | {:<{}} | {}\n", mod.key, keyLength, mod.firstAuthor, authorLength, mod.version);
			}
		}
		catch (...) {
			output << "Failed to process lua mods." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}

namespace CrashLogger::Warnings {
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			// Dump Warnings.txt.
			if (!std::filesystem::exists("Warnings.txt")) {
				return;
			}

			std::ifstream warnings("Warnings.txt");
			if (!warnings.is_open()) {
				return;
			}

			std::unordered_set<std::string> seenLines;
			std::string line;
			while (std::getline(warnings, line)) {
				if (line.empty()) continue;
				if (seenLines.find(line) == seenLines.end()) {
					output << line << std::endl;
					seenLines.insert(line);
				}
			}

			warnings.close();
		}
		catch (...) {
			output << "Failed to log warnings." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}
