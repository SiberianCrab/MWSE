#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "NITriShape.h"
#include "NIProperty.h"

namespace se::cs::dialog::layer_window {

	struct NodeColorData {
		NI::Pointer<NI::MaterialProperty> originalMaterial = nullptr;
		NI::Pointer<NI::AlphaProperty> originalAlphaProperty = nullptr;
		NI::Pointer<NI::VertexColorProperty> originalVColorProperty = nullptr;

	};

	struct LayerData {
		std::unordered_map<Cell*, std::unordered_set<Reference*>> perCellReferences;
		std::unordered_map<NI::TriShape*, NodeColorData*> nodeMaterialData;

		std::string layerName;
		bool isOverlayActive = false;
		bool isLayerHidden = false;

		NI::Color layerOverlayColor = NI::Color{ 0.0f, 1.0f, 0.4f }; //rbg for some reason
		NI::Pointer<NI::MaterialProperty> layerOverlayMaterial = nullptr;

		void setLayerColor(const NI::Color& c) { layerOverlayColor = c; }
		NI::Color getLayerColor() const { return layerOverlayColor; }
	};

	void createLayersWindow();
	void toggleLayersWindow(bool show);

	void forceToggleLayersWindow(HMENU viewMenu);
	void refreshLayersMenuItem(HMENU viewMenu);
	bool IsRenderWindowVisible(HMENU viewMenu);

	std::vector<LayerData>& GetLayers();

	extern HWND hLayersWnd;
}