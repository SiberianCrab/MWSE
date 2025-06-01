#include "CrashLogger.hpp"

namespace CrashLogger {
	inline bool GetStringForClassLabel(void* object, std::string& labelName, std::string& objectName, std::string& description) {
		try {
			static bool fillLables = false;

			if (!fillLables) {
				Labels::FillLabels();
				fillLables = true;
			}

			for (const auto& iter : Labels::Label::GetAll()) if (iter && iter->Satisfies(object)) {
				labelName = iter->GetLabelName();
				objectName = iter->GetName(object);
				description = iter->GetDescription(object);
				return true;
			}
			return false;
		}
		catch (...) {
			return false;
		}
	}

	bool GetAsString(const void* object, std::string& labelName, std::string& string) {
		try {
			const auto printable = [](const char a_ch) noexcept {
				if (' ' <= a_ch && a_ch <= '~') return true;

				switch (a_ch) {
				case '\t':
				case '\n':
					return true;
				default:
					return false;
				}
			};
			const auto cstr = static_cast<const char*>(object);
			if (object == NULL || cstr == NULL) return false;
			constexpr std::size_t max = MAX_PATH;
			std::size_t len = 0;
			for (; len < max && cstr && cstr[len] != '\0'; ++len) {
				if (!printable(cstr[len])) {
					return false;
				}
			}
			if (len == 0 || len >= max || len < 3) return false;
			const auto& str = SanitizeString(cstr);
			// Check if string is equal to a predefined prefix and print out the file name if true
			// TODO: This surely is still not needed, or at least needs updating.
			if (const auto pos = str.find("D:\\_Fallout3\\"); pos == std::string::npos) {
				labelName = "String";
				string = str;
			}
			else {
				const std::filesystem::path path = str.substr(pos);
				labelName = "Source";
				string = path.filename().string();
			}
			return true;
		}
		catch (...) {
			return false;
		}

	}
}

namespace CrashLogger::Registry {
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			output << fmt::format("REG | {:^10} | DEREFERENCE INFO", "Value") << '\n';

			const std::map<std::string, UINT32> registers{
				{ "eax", info->ContextRecord->Eax },
				{ "ebx", info->ContextRecord->Ebx },
				{ "ecx", info->ContextRecord->Ecx },
				{ "edx", info->ContextRecord->Edx },
				{ "edi", info->ContextRecord->Edi },
				{ "esi", info->ContextRecord->Esi },
				{ "ebp", info->ContextRecord->Ebp },
				{ "esp", info->ContextRecord->Esp },
				{ "eip", info->ContextRecord->Eip },
			};

			for (const auto& [name, value] : registers) {
				std::stringstream str;
				str << fmt::format("{} | 0x{:08X} | ", name, value);
				std::string buffer = Stack::GetLineForObject((void**)value, 5);
				if (!buffer.empty() && buffer != "") {
					str << buffer;
				}
				output << str.str() << '\n';
			}
		}
		catch (...) {
			output << "Failed to log registry." << '\n';
		}
	}

	extern std::stringstream& Get() { output.flush(); return output; }
}

namespace CrashLogger::Stack {
	std::map<UINT32, UINT8> memoize;

	std::stringstream output;

	bool GetStringForRTTIorPDB(void** object, std::string& buffer) {
		try {
			//		if (*(UINT32*)object > VFTableLowerLimit() && *(UINT32*)object < 0x1200000)
			if (const auto& name = PDB::GetClassNameFromRTTIorPDB((void*)object); !name.empty()) {
				buffer += fmt::format("0x{:08X} ==> RTTI: ", *(UINT32*)object) + name;
				return true;
			}
			return false;
		}
		catch (...) {
			return false;
		}
	}

	bool GetStringForLabel(void** object, std::string& buffer) {
		try {
			std::string labelName, objectName, description;
			if (GetStringForClassLabel(object, labelName, objectName, description)) {
				buffer += fmt::format("0x{:08X} ==> ", *(UINT32*)object) + labelName + ": " + objectName + ": " + description;
				return true;
			}
			if (GetStringForRTTIorPDB(object, buffer)) {
				return true;
			}

			if (GetAsString(object, labelName, description)) {
				buffer += fmt::format("0x{:08X} ==> ", *(UINT32*)object) + labelName + ": " + '"' + description + '"';
				return true;
			}
			return false;
		}
		catch (...) {
			return false;
		}
	}

	bool GetStringForLabelSEH(void** object, std::string& buffer) {
		__try {
			return GetStringForLabel(object, buffer);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
	}

	std::string GetLineForObject(void** object, UINT32 depth) {
		if (!object) return "";
		std::string buffer;
		UINT32 deref = 0;
		do {
			if (GetStringForLabelSEH(object, buffer)) {
				return buffer;
			}
			deref = Dereference<UINT32>(object);
			buffer += fmt::format("0x{:08X} ==> ", deref);
			object = (void**)deref;
			depth--;
		} while (object && depth);

		return "";
	}

	UINT32 GetESPi(UINT32* esp, UINT32 i) try { return esp[i]; }
	catch (...) { return 0; }

	extern void Process(EXCEPTION_POINTERS* info) {
		try {
			output << fmt::format("  # | {:^10} | DEREFERENCE INFO", "Value") << '\n';
			const auto esp = reinterpret_cast<UINT32*>(info->ContextRecord->Esp);
			std::vector<int> iotaVec(0x100);
			std::iota(iotaVec.begin(), iotaVec.end(), 0);
			for (unsigned int i : iotaVec) {
				const auto espi = GetESPi(esp, i);
				const auto str = Stack::GetLineForObject((void**)espi, 5);
				if (i <= 0x8 || (!str.empty() && memoize.find(espi) == memoize.end())) {
					std::stringstream line;
					line << fmt::format(" {:2X} | 0x{:08X} | ", i, espi);
					if (memoize.find(espi) == memoize.end()) {
						if (!str.empty()) line << str;
						memoize.emplace(espi, i);
					}
					else {
						line << fmt::format("Identical to {:2X}", memoize[espi]);
					}
					output << line.str() << '\n';

				}
			}
		}
		catch (...) {
			output << "Failed to log stack." << '\n';
		}
	}

	extern std::stringstream& Get() {
		output.flush();
		return output;
	}
}