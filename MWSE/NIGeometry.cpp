#include "NIGeometry.h"

namespace NI {
	GeometryData* Geometry::getModelData() {
		return modelData;
	}

	void Geometry::setModelData(GeometryData* data) {
		vTable.asGeometry->setModelData(this, data);
	}
}

MWSE_SOL_CUSTOMIZED_PUSHER_DEFINE_NI(NI::Geometry)
