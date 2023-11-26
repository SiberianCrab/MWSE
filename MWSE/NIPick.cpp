#include "NIPick.h"

#include "MemoryUtil.h"
#include "NIUtil.h"

#include "NIPointer.h"
#include "NISkinInstance.h"
#include "NITriShape.h"
#include "NiTriShapeData.h"

namespace NI {
	const auto TES3_Pick_ctor = reinterpret_cast<Pick*(__thiscall*)(Pick*)>(0x6F2DF0);
	Pick* Pick::malloc() {
		return TES3_Pick_ctor(mwse::tes3::malloc<Pick>());
	}

	const auto TES3_Pick_dtor = reinterpret_cast<void(__thiscall*)(Pick*)>(0x6F2EA0);
	void Pick::free() {
		TES3_Pick_dtor(this);
		mwse::tes3::free(this);
	}

	const auto TES3_Pick_pickObjects = reinterpret_cast<bool(__thiscall*)(Pick*, const TES3::Vector3*, const TES3::Vector3*, bool, float)>(0x6F3050);
	bool Pick::pickObjects(const TES3::Vector3 * origin, const TES3::Vector3 * direction, bool append, float maxDistance) {
		return TES3_Pick_pickObjects(this, origin, direction, append, maxDistance);
	}

	struct SavedGeometryState {
		Pointer<TriShape> geometry;
		Pointer<TriShapeData> data;
		Pointer<SkinInstance> skinInstance;
	};

	bool Pick::pickObjectsWithSkinDeforms(const TES3::Vector3 * origin, const TES3::Vector3* direction, bool append, float maxDistance) {
		// Data to restore skinned objects to their original state.
		std::vector<SavedGeometryState> savedGeometryStates;

		const auto previousPickType = pickType;
		pickType = NI::PickType::FIND_ALL;

		// Perform our first test.
		if (!pickObjects(origin, direction, append, maxDistance)) {
			pickType = previousPickType;
			return false;
		}

		// Store if a redo is needed.
		auto needsRedo = false;

		// Check to see if any skinned objects were hit.
		for (auto& result : results) {
			if (result == nullptr) {
				continue;
			}

			// Skip if we're not affecting tri-based geometry.
			if (!result->object->isInstanceOfType(RTTIStaticPtr::NiTriShape)) {
#if _DEBUG
				if (result->object->skinInstance) {
					pickType = previousPickType;
					throw std::exception("Unaccounted for type of skinned object!");
				}
#endif
				continue;
			}

			const auto geometry = static_cast<TriShape*>(result->object);

			// If the geometry is skinned we apply the skin deform and set the redo flag.
			// This way the redo raycast (and future raycasts) can handle the object correctly.
			if (geometry->skinInstance) {
				needsRedo = true;

				// Create our backup data.
				savedGeometryStates.push_back({});
				auto& backup = savedGeometryStates.back();
				backup.geometry = geometry;

				// Clone the data.
				backup.data = geometry->getModelData();
				auto data = backup.data->cloneData(true, false, false);
				data->bounds = backup.data->bounds;
				geometry->setModelData(data);

				// Apply the skin deform to the new copy.
				geometry->skinInstance->deform(backup.data->vertex, backup.data->normal, data->vertexCount, data->vertex, data->normal);
				data->markAsChanged();

				// Backup and clear skin instance.
				backup.skinInstance = geometry->skinInstance;
				geometry->skinInstance = nullptr;

				geometry->update();
			}
		}

		// Perform another raytest if necessary.
		// TODO: To optimize this further, perform a second pick in another root with only the skinned geometry, and update the existing distances.
		auto result = true;
		if (needsRedo) {
			pickType = previousPickType;
			clearResults();
			result = pickObjects(origin, direction, append, maxDistance);
		}

		// Restore existing geomtry data.
		for (const auto& state : savedGeometryStates) {
			state.geometry->setModelData(state.data);
			state.geometry->skinInstance = state.skinInstance;
			state.geometry->update();
		}

		pickType = previousPickType;
		return result;
	}

	const auto TES3_Pick_clearResults = reinterpret_cast<void(__thiscall*)(Pick*)>(0x6F2F80);
	void Pick::clearResults() {
		TES3_Pick_clearResults(this);
	}

	std::reference_wrapper<unsigned short[3]> PickRecord::getVertexIndex() {
		return std::ref(vertexIndex);
	}

	TES3::Reference* PickRecord::getTES3Reference() {
		return getAssociatedReference(object);
	}
}
