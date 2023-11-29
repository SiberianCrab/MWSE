#include "CSSpell.h"

#include "StringUtil.h"

namespace se::cs {
	bool Spell::getSpellFlag(SpellFlag::Flag flag) const {
		return (spellFlags & flag) == flag;
	}

	bool Spell::getPlayerStart() const {
		return getSpellFlag(SpellFlag::PCStartSpell);
	}

	bool Spell::search(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		if (Object::search(needle, caseSensitive, regex)) {
			return true;
		}

		return false;
	}
}
