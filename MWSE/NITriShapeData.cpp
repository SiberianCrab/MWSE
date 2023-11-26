#include "NITriShapeData.h"

#include "LuaUtil.h"
#include "MemoryUtil.h"

namespace NI {
	const auto NI_TriShapeData_ctor = reinterpret_cast<void(__thiscall*)(TriShapeData*, unsigned short, TES3::Vector3*, TES3::Vector3*, PackedColor*, TES3::Vector2*, unsigned short, Triangle*, int)>(0x6E4690);
	Pointer<TriShapeData> TriShapeData::create(unsigned short _vertexCount, TES3::Vector3* _vertices, TES3::Vector3* _normals, PackedColor* _colors, TES3::Vector2* _textureCoords, unsigned short _triangleCount, Triangle* _triangleList, int unused) {
		auto ptr = mwse::tes3::_new<TriShapeData>();
		NI_TriShapeData_ctor(ptr, _vertexCount, _vertices, _normals, _colors, _textureCoords, _triangleCount, _triangleList, unused);
		return ptr;
	}

	Pointer<TriShapeData> TriShapeData::create(unsigned short vertexCount, bool hasNormals, bool hasColors, unsigned short textureCoordSets, unsigned short triangleCount) {
		using TES3::Vector2;
		using TES3::Vector3;

		Vector3* vertices = mwse::tes3::_new<Vector3>(vertexCount);
		ZeroMemory(vertices, sizeof(Vector3) * vertexCount);

		Vector3* normals = nullptr;
		if (hasNormals) {
			normals = mwse::tes3::_new<Vector3>(vertexCount);
			ZeroMemory(normals, sizeof(Vector3) * vertexCount);
		}

		PackedColor* colors = nullptr;
		if (hasColors) {
			colors = mwse::tes3::_new<PackedColor>(vertexCount);
			ZeroMemory(colors, sizeof(PackedColor) * vertexCount);
		}

		Vector2* textureCoords = nullptr;
		if (textureCoordSets > 0) {
			size_t textureCoordTotal = textureCoordSets * vertexCount;
			textureCoords = mwse::tes3::_new<Vector2>(textureCoordTotal);
			ZeroMemory(textureCoords, sizeof(Vector2) * textureCoordTotal);
		}

		Triangle* triangleList = nullptr;
		if (triangleCount) {
			triangleList = mwse::tes3::_new<Triangle>(triangleCount);
			ZeroMemory(triangleList, sizeof(Triangle) * triangleCount);
		}

		// Create data and update texture set count after creation, as the constructor call assumes there is only 0 or 1 texture set.
		auto result = create(vertexCount, vertices, normals, colors, textureCoords, triangleCount, triangleList);
		result->textureSets = textureCoordSets;
		return result;
	}

	Pointer<TriShapeData> TriShapeData::cloneData(bool copyNormals, bool copyColors, bool copyTextureCoordinates) const {
		auto vertexCount = getActiveVertexCount();

		TES3::Vector3* _vertices = mwse::tes3::_new<TES3::Vector3>(vertexCount);
		memcpy_s(_vertices, sizeof(TES3::Vector3) * vertexCount, vertex, sizeof(TES3::Vector3) * vertexCount);

		TES3::Vector3* _normals = nullptr;
		if (normal && copyNormals) {
			_normals = mwse::tes3::_new<TES3::Vector3>(vertexCount);
			memcpy_s(_normals, sizeof(TES3::Vector3) * vertexCount, normal, sizeof(TES3::Vector3) * vertexCount);
		}

		PackedColor* _colors = nullptr;
		if (color && copyColors) {
			_colors = mwse::tes3::_new<PackedColor>(vertexCount);
			memcpy_s(_colors, sizeof(PackedColor) * vertexCount, color, sizeof(PackedColor) * vertexCount);
		}

		TES3::Vector2* _textureCoords = nullptr;
		if (textureCoords && copyTextureCoordinates) {
			_textureCoords = mwse::tes3::_new<TES3::Vector2>(vertexCount);
			memcpy_s(_textureCoords, sizeof(TES3::Vector2) * vertexCount, textureCoords, sizeof(TES3::Vector2) * vertexCount);
		}

		Triangle* _triangleList = nullptr;
		if (triangleList) {
			_triangleList = mwse::tes3::_new<Triangle>(triangleCount);
			memcpy_s(_triangleList, sizeof(Triangle) * triangleCount, triangleList, sizeof(Triangle) * triangleCount);
		}

		auto result = create(vertexCount, _vertices, _normals, _colors, _textureCoords, triangleCount, _triangleList);

		// Copy over any other necessary data.
		result->bounds = bounds;

		return result;
	}

	Pointer<TriShapeData> TriShapeData::copyData(sol::optional<sol::table> filters) const {
		auto vertexCount = getActiveVertexCount();

		TES3::Vector3* _vertices = mwse::tes3::_new<TES3::Vector3>(vertexCount);
		memcpy_s(_vertices, sizeof(TES3::Vector3) * vertexCount, vertex, sizeof(TES3::Vector3) * vertexCount);

		TES3::Vector3* _normals = nullptr;
		if (normal && mwse::lua::getOptionalParam(filters, "normals", true)) {
			_normals = mwse::tes3::_new<TES3::Vector3>(vertexCount);
			memcpy_s(_normals, sizeof(TES3::Vector3) * vertexCount, normal, sizeof(TES3::Vector3) * vertexCount);
		}

		PackedColor* _colors = nullptr;
		if (color && mwse::lua::getOptionalParam(filters, "colors", true)) {
			_colors = mwse::tes3::_new<PackedColor>(vertexCount);
			memcpy_s(_colors, sizeof(PackedColor) * vertexCount, color, sizeof(PackedColor) * vertexCount);
		}

		TES3::Vector2* _textureCoords = nullptr;
		if (textureCoords && mwse::lua::getOptionalParam(filters, "texCoords", true)) {
			size_t textureCoordTotal = textureSets * vertexCount;
			_textureCoords = mwse::tes3::_new<TES3::Vector2>(textureCoordTotal);
			memcpy_s(_textureCoords, sizeof(TES3::Vector2) * textureCoordTotal, textureCoords, sizeof(TES3::Vector2) * textureCoordTotal);
		}

		Triangle* _triangleList = nullptr;
		if (triangleList) {
			_triangleList = mwse::tes3::_new<Triangle>(triangleCount);
			memcpy_s(_triangleList, sizeof(Triangle) * triangleCount, triangleList, sizeof(Triangle) * triangleCount);
		}

		// Create data and update texture set count after creation, as the constructor call assumes there is only 0 or 1 texture set.
		auto result = create(vertexCount, _vertices, _normals, _colors, _textureCoords, triangleCount, _triangleList);
		result->textureSets = _textureCoords ? textureSets : 0;
		result->bounds = bounds;

		return result;
	}

	nonstd::span<Triangle> TriShapeData::getTriangles() {
		if (triangleList) {
			return { triangleList, getActiveTriangleCount() };
		}
		return {};
	}
}
