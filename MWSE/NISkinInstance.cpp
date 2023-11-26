#include "NISkinInstance.h"

namespace NI {
	nonstd::span<unsigned short> SkinPartition::Partition::getBones() {
		if (bones) {
			return nonstd::span<unsigned short>(bones, numBones);
		}
		return {};
	}

	nonstd::span<unsigned short> SkinPartition::Partition::getStripLengths() {
		if (bones) {
			return nonstd::span<unsigned short>(stripLengths, numStripLengths);
		}
		return {};
	}

	nonstd::span<Triangle> SkinPartition::Partition::getTriangles() {
		if (triangles) {
			return nonstd::span<Triangle>(triangles, numTriangles);
		}
		return {};
	}

	nonstd::span<unsigned short> SkinPartition::Partition::getVertices() {
		if (vertices) {
			return nonstd::span<unsigned short>(vertices, numVertices);
		}
		return {};
	}

	nonstd::span<SkinPartition::Partition> SkinPartition::getPartitions() {
		if (partitions) {
			return nonstd::span<Partition>(partitions, partitionCount);
		}
		return {};
	}

	nonstd::span<SkinData::BoneData::VertexWeight> SkinData::BoneData::getWeights() {
		if (weights) {
			return nonstd::span<VertexWeight>(weights, weightCount);
		}
		return {};
	}

	nonstd::span<SkinData::BoneData> SkinData::getBones() {
		if (boneData) {
			return nonstd::span<BoneData>(boneData, numBones);
		}
		return {};
	}

	const auto NI_SkinInstance_Deform = reinterpret_cast<void(__thiscall*)(const NI::SkinInstance*, const TES3::Vector3*, size_t, const TES3::Vector3*, size_t, TES3::Vector3*, TES3::Vector3*, size_t)>(0x6FA000);
	void SkinInstance::deform(const TES3::Vector3* srcVertices, const TES3::Vector3* srcNormals, unsigned int vertexCount, TES3::Vector3* dstVertices, TES3::Vector3* dstNormals) const {
		return NI_SkinInstance_Deform(this, srcVertices, sizeof(TES3::Vector3), srcNormals, vertexCount, dstVertices, dstNormals, sizeof(TES3::Vector3));
	}

	nonstd::span<AVObject*> SkinInstance::getBoneObjects() {
		if (bones) {
			return nonstd::span<AVObject*>(bones, skinData->numBones);
		}
		return {};
	}
}
