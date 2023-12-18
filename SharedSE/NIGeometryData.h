#pragma once

#include "NIBound.h"
#include "NIObject.h"
#include "NIVector2.h"

namespace NI {
	struct GeometryData_vTable : Object_vTable {
		void(__thiscall* setActiveVertexCount)(GeometryData*, unsigned short); // 0x2C
		unsigned short(__thiscall* getActiveVertexCount)(const GeometryData*); // 0x30
		void(__thiscall* calculateNormals)(GeometryData*); // 0x34
	};
	static_assert(sizeof(GeometryData_vTable) == 0x38, "NI::GeometryData_vTable failed size validation");

	struct GeometryData : Object {
		unsigned short vertexCount; // 0x8
		unsigned short textureSets; // 0xA
		Bound bounds; // 0xC
		Vector3* vertex; // 0x1C
		Vector3* normal; // 0x20
		PackedColor* color; // 0x24
		Vector2* textureCoords; // 0x28
		unsigned int uniqueID; // 0x2C
		unsigned short revisionID; // 0x30
		bool unknown_0x32;

		//
		// vTable wrappers.
		//

		unsigned short getActiveVertexCount() const;

		//
		// Custom functions.
		//

		nonstd::span<Vector3> getVertices() const;
		void markAsChanged();
		void updateModelBound();
	};
	static_assert(sizeof(GeometryData) == 0x34, "NI::GeometryData failed size validation");
}
