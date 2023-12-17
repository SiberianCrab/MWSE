#include "LuaKeyframesLoadedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3ActorAnimationController.h"

#include "NIKeyframeManager.h"

namespace mwse::lua::event {
	KeyframesLoadedEvent::KeyframesLoadedEvent(const char* path, const char* sequenceName, TES3::KeyframeDefinition* keyframeDefinition) :
		GenericEvent("keyframesLoaded"),
		m_Path(path),
		m_SequenceName(sequenceName),
		m_KeyframeDefinition(keyframeDefinition)
	{
	}

	sol::table KeyframesLoadedEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.state;
		auto eventData = state.create_table();

		eventData["path"] = m_Path;
		eventData["sequenceName"] = m_SequenceName;
		// eventData["keyframeDefinition"] = m_KeyframeDefinition;

		auto sequence = m_KeyframeDefinition->sequences[0];
		if (sequence) {
			eventData["textKeys"] = sequence->textKeys;
		}

		return eventData;
	}

	sol::object KeyframesLoadedEvent::getEventOptions() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.state;
		auto options = state.create_table();
		options["filter"] = m_Path;
		return options;
	}

	bool KeyframesLoadedEvent::m_EventEnabled = false;
}
