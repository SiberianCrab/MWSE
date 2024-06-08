#include "LuaUiSpellTooltipEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Spell.h"
#include "TES3UIElement.h"

namespace mwse::lua::event {
	UiSpellTooltipEvent::UiSpellTooltipEvent(TES3::UI::Element* tooltip, TES3::Spell* spell) :
		ObjectFilteredEvent("uiSpellTooltip", spell),
		m_Tooltip(tooltip),
		m_Spell(spell)
	{

	}

	sol::table UiSpellTooltipEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.state;
		auto eventData = state.create_table();

		eventData["tooltip"] = m_Tooltip;
		eventData["spell"] = m_Spell;

		return eventData;
	}
}
