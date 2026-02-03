#pragma once

#include "LuaUtil.h"
#include "StringUtil.h"

#include "NIObjectLua.h"
#include "NIDefines.h"
#include "NIDynamicEffect.h"

namespace mwse::lua {
	auto traverse(const NI::Node* self, sol::optional<sol::table> param) {
		bool recursive = getOptionalParam(param, "recursive", true);
		std::string prefix = getOptionalParam(param, "prefix", std::string(""));
		std::unordered_set<unsigned int> filters;

		if (param) {
			sol::table paramTable = param.value().as<sol::table>();
			sol::object maybeValue = paramTable["type"];
			if (maybeValue.valid()) {
				if (maybeValue.is<unsigned int>()) {
					filters.insert(maybeValue.as<unsigned int>());
				}
				else if (maybeValue.is<sol::table>()) {
					sol::table filterTable = maybeValue.as<sol::table>();
					for (auto [_, value] : filterTable) {
						filters.insert(value.as<unsigned int>());
					}
				}
				else {
					throw std::invalid_argument("Iteration can only be filtered by a NI object type, or a table of object types.");
				}
			}
		}


		std::queue<NI::Pointer<NI::AVObject>> queue;
		std::function<void(const NI::AVObject*)> traverseChild = [&](const NI::AVObject* object) {
			if (!object->isInstanceOfType(NI::RTTIStaticPtr::NiNode)) {
				return;
			}

			const auto asNode = static_cast<const NI::Node*>(object);
			for (auto& nodeChild : asNode->children) {
				if (!nodeChild) {
					continue;
				}
				bool passesFilter = filters.empty() ? true : false;
				if (!passesFilter) {
					for (const auto type : filters) {
						if (nodeChild->isInstanceOfType((uintptr_t)type)) {
							passesFilter = true;
							break;
						}
					}
				}
				bool passesPrefix = prefix.empty() ? true : nodeChild->name && mwse::string::starts_with(nodeChild->name, prefix);
				if (passesFilter && passesPrefix) {
					queue.push(nodeChild);
				}

				traverseChild(nodeChild);
			}
		};

		for (auto& child : self->children) {
			if (!child) {
				continue;
			}
			bool passesFilter = filters.empty() ? true : false;
			if (!passesFilter) {
				for (const auto type : filters) {
					if (child->isInstanceOfType((uintptr_t)type)) {
						passesFilter = true;
						break;
					}
				}
			}
			bool passesPrefix = prefix.empty() ? true : child->name && mwse::string::starts_with(child->name, prefix);
			if (passesFilter && passesPrefix) {
				queue.push(child);
			}
			if (recursive) {
				traverseChild(child);
			}
		}

		return [queue]() mutable -> NI::Pointer<NI::AVObject> {
			if (queue.empty()) {
				return nullptr;
			}
			auto ret = queue.front();
			queue.pop();
			return ret;
		};
	}

	template <typename T>
	void setUserdataForNINode(sol::usertype<T>& usertypeDefinition) {
		setUserdataForNIAVObject(usertypeDefinition);

		// Basic property binding.
		usertypeDefinition["children"] = sol::readonly_property(&NI::Node::children);
		usertypeDefinition["effectList"] = sol::readonly_property(&NI::Node::effectList);

		// Basic function binding.
		usertypeDefinition["attachChild"] = &NI::Node::attachChild_lua;
		usertypeDefinition["attachEffect"] = &NI::Node::attachEffect;
		usertypeDefinition["createBoundingBox"] = &NI::Node::createBoundingBox_lua;
		usertypeDefinition["detachAllChildren"] = &NI::Node::detachAllChildren;
		usertypeDefinition["detachAllEffects"] = &NI::Node::detachAllEffects;
		usertypeDefinition["detachChild"] = &NI::Node::detachChild;
		usertypeDefinition["detachChildAt"] = &NI::Node::detachChildAt_lua;
		usertypeDefinition["detachEffect"] = &NI::Node::detachEffect;
		usertypeDefinition["getEffect"] = &NI::Node::getEffect;
		usertypeDefinition["traverse"] = traverse;
	}

	void bindNINode();
}
