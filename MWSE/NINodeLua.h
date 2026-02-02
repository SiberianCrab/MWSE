#pragma once

#include "NIObjectLua.h"
#include "NIDefines.h"
#include "NIDynamicEffect.h"

namespace mwse::lua {
	auto traverse(const NI::Node* node) {
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
				queue.push(nodeChild);
				traverseChild(nodeChild);
			}
		};

		for (auto& child : node->children) {
			if (!child) {
				continue;
			}
			queue.push(child);
			traverseChild(child);
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
