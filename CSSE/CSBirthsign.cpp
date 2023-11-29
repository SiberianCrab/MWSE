#include "CSBirthsign.h"

#include "StringUtil.h"

namespace se::cs {
	bool Birthsign::search(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		if (BaseObject::search(needle, caseSensitive, regex)) {
			return true;
		}

		if (name && string::complex_contains(name, needle, caseSensitive, regex)) {
			return true;
		}

		if (description && string::complex_contains(description, needle, caseSensitive, regex)) {
			return true;
		}

		return false;
	}
}
