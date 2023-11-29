#include "CSObject.h"

#include "CSBirthsign.h"
#include "CSBook.h"
#include "CSClass.h"
#include "CSFaction.h"
#include "CSRace.h"
#include "CSScript.h"
#include "CSSpell.h"

#include "StringUtil.h"

namespace se::cs {
	bool Object::search(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		if (BaseObject::search(needle, caseSensitive, regex)) {
			return true;
		}

		const auto name = getName();
		if (name && string::complex_contains(name, needle, caseSensitive, regex)) {
			return true;
		}

		const auto script = getScript();
		if (script && string::complex_contains(script->getObjectID(), needle, caseSensitive, regex)) {
			return true;
		}

		return false;
	}

	bool Object::searchWithInheritance(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		switch (objectType) {
		case ObjectType::Book:
			return static_cast<const Book*>(this)->search(needle, caseSensitive, regex);
		case ObjectType::Spell:
			return static_cast<const Spell*>(this)->search(needle, caseSensitive, regex);
		}

		// Do the usual object searches then pass off to BaseObject tests.
		if (search(needle, caseSensitive, regex)) {
			return true;
		}

		// TODO: This searches the ID twice.
		return BaseObject::searchWithInheritance(needle, caseSensitive, regex);
	}
}
