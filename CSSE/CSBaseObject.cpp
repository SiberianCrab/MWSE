#include "CSBaseObject.h"

#include "CSBirthsign.h"
#include "CSClass.h"
#include "CSFaction.h"
#include "CSScript.h"
#include "CSRace.h"

#include "StringUtil.h"

namespace se::cs {
	const char* BaseObject::getObjectID() const {
		return vtbl.baseObject->getObjectID(this);
	}

	bool BaseObject::isFromMaster() const {
		return (flags & 0x1);
	}

	bool BaseObject::getModified() const {
		return (flags & 0x2);
	}

	void BaseObject::setModified(bool modified) {
		vtbl.baseObject->setObjectModified(this, modified);
	}

	bool BaseObject::getDeleted() const {
		return (flags & 0x20);
	}

	bool BaseObject::getPersists() const {
		return (flags & 0x400);
	}

	bool BaseObject::getBlocked() const {
		return (flags & 0x2000);
	}

	void BaseObject::setFlag80(bool set) {
		const auto BaseObject_setFlag80 = reinterpret_cast<void(__thiscall*)(BaseObject*, bool)>(0x4019E7);
		BaseObject_setFlag80(this, set);
	}

	bool BaseObject::search(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		return string::complex_contains(getObjectID(), needle, caseSensitive, regex);
	}

	bool BaseObject::searchWithInheritance(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		switch (objectType) {
		case ObjectType::Birthsign:
			return static_cast<const Birthsign*>(this)->search(needle, caseSensitive, regex);
		case ObjectType::Class:
			return static_cast<const Class*>(this)->search(needle, caseSensitive, regex);
		case ObjectType::Faction:
			return static_cast<const Faction*>(this)->search(needle, caseSensitive, regex);
		case ObjectType::Script:
			return static_cast<const Script*>(this)->search(needle, caseSensitive, regex);
		case ObjectType::Race:
			return static_cast<const Race*>(this)->search(needle, caseSensitive, regex);
		}

		// Fall back to just an ID search.
		return search(needle, caseSensitive, regex);
	}
}
