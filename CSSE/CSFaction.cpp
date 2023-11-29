#include "CSFaction.h"

#include "StringUtil.h"

namespace se::cs {
	bool Faction::search(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		if (BaseObject::search(needle, caseSensitive, regex)) {
			return true;
		}

		if (string::complex_contains(name, needle, caseSensitive, regex)) {
			return true;
		}

		for (const auto& rank : rankNames) {
			if (string::complex_contains(rank, needle, caseSensitive, regex)) {
				return true;
			}
		}

		return false;
	}
}
