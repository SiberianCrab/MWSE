#pragma once

#include "TES3Defines.h"

namespace mwse::lua {
	class ScriptContext;
}

namespace TES3 {
	struct ItemDataVanilla {
		int count; // 0x0
		BaseObject* owner; // 0x4
		union {
			long requiredRank;
			GlobalVariable* requiredVariable;
		}; // 0x8
		union {
			int condition;
			float timeLeft;
		}; // 0xC
		union {
			float charge;
			Actor* soul;
		}; // 0x10
		Script* script; // 0x14
		ScriptVariables* scriptData; // 0x18

		//
		// Basic operators.
		//

		static void* operator new(size_t size);
		static void operator delete(void* block);

		//
		// Related static functions.
		// 

		static ItemDataVanilla* __fastcall ctor(ItemDataVanilla* self);
		static void __fastcall dtor(ItemDataVanilla* self);

		static ItemDataVanilla* __fastcall createForObject(Object* object);

	};
	static_assert(sizeof(ItemDataVanilla) == 0x1C, "TES3::ItemData failed size validation");


	namespace ItemDataFlags {
		typedef unsigned int value_type;

		enum {
			ItemDataFlag_BoundItem = 1,
		};
	}

	struct ItemData : ItemDataVanilla {
		class LuaData {
		public:
			LuaData();

			sol::table data;
			sol::table tempData;
		};
		LuaData* luaData;
		ItemDataFlags::value_type flags;

		//
		// Overrides for vanilla handlers.
		//

		ItemData();
		~ItemData();

		static ItemData* __fastcall ctor(ItemData* self);
		static void __fastcall dtor(ItemData* self);

		static ItemData* __cdecl createForObject(Object* object);
		static ItemData* __cdecl createForBoundItem(Object* object);

		static bool __cdecl isItemDataStackable(ItemData* itemData, Item* item, bool ignoreOwnership = false);

		//
		// Custom functions.
		//

		TES3::BaseObject* getOwner() const;
		void setOwner_lua(sol::object value);

		sol::object getOwnerRequirement_lua(sol::this_state ts) const;
		void setOwnerRequirement_lua(sol::object value);

		Actor* getSoul() const;
		void setSoul_lua(sol::object actor);
		bool isBoundItem() const;

		void setLuaDataTable(sol::object data);
		void setLuaTempDataTable(sol::object data);
		sol::table getOrCreateLuaDataTable();
		sol::table getOrCreateLuaTempDataTable();

		std::shared_ptr<mwse::lua::ScriptContext> createContext();
		bool setScriptShortValue(const char* name, short value);
	};
}
