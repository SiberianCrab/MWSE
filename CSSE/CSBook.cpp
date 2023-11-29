#include "CSBook.h"

#include "CSDataHandler.h"
#include "CSRecordHandler.h"
#include "CSGameSetting.h"

#include "StringUtil.h"

namespace se::cs {
	const char* Book::getTaughtSkillName() const {
		const auto gmst = DataHandler::get()->recordHandler->getGameSettingForSkill(skillId);
		if (gmst == nullptr) {
			return "";
		}

		return gmst->value.asString;
	}

	bool Book::search(const std::string_view& needle, bool caseSensitive, std::regex* regex) const {
		if (Object::search(needle, caseSensitive, regex)) {
			return true;
		}

		if (text && string::complex_contains(text, needle, caseSensitive, regex)) {
			return true;
		}

		return false;
	}
}
