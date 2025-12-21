#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "CSCell.h"
#include "CSRecordHandler.h"
#include "CSDataHandler.h"
#include "NIIteratedList.h"
#include "CSReference.h"
#include "NITriShape.h"
#include "NIProperty.h"

constexpr size_t HIDDEN_LAYER_ID = 0;

namespace se::cs::dialog::layer_window {

	struct NodeColorData {
		NI::Pointer<NI::MaterialProperty> originalMaterial = nullptr;
		NI::Pointer<NI::AlphaProperty> originalAlphaProperty = nullptr;
		NI::Pointer<NI::VertexColorProperty> originalVColorProperty = nullptr;
	};

	struct LayerData {
		std::unordered_map<Cell*, std::unordered_set<Reference*>> perCellReferences;
		std::unordered_map<NI::TriShape*, NodeColorData*> nodeMaterialData;

		size_t id = 0;
		std::string* layerName = nullptr;
		bool isOverlayActive = false;
		bool isLayerHidden = false;

		NI::Color layerOverlayColor = NI::Color{ 0.0f, 1.0f, 0.4f }; //rbg for some reason
		NI::Pointer<NI::MaterialProperty> layerOverlayMaterial = nullptr;
		NI::Pointer<NI::AlphaProperty> layerAlphaProperty = nullptr;
		NI::Pointer<NI::VertexColorProperty> layerVertexColorProperty = nullptr;

		~LayerData() noexcept
		{
			for (auto& kv : nodeMaterialData) {
				NodeColorData* p = kv.second;
				if (p) {
					delete p;
				}
			}
			nodeMaterialData.clear();

			if (layerName) {
				delete layerName;
				layerName = nullptr;
			}

			perCellReferences.clear();

			layerOverlayMaterial = nullptr;
			layerAlphaProperty = nullptr;
			layerVertexColorProperty = nullptr;
		}

		NI::Color getLayerColor() const { return layerOverlayColor; }
		void setLayerColor(const NI::Color& c) { 
			layerOverlayColor = c;
			if (layerOverlayMaterial) {
				layerOverlayMaterial->setEmissive(layerOverlayColor);
				layerOverlayMaterial->setDiffuse(layerOverlayColor);
				layerOverlayMaterial->setAmbient(layerOverlayColor);
			}
		}

		NI::Pointer<NI::MaterialProperty> getLayerOverlayMaterial(NI::Pointer<NI::MaterialProperty> material) {
			if (!layerOverlayMaterial && material) {
				layerOverlayMaterial = static_cast<NI::MaterialProperty*>(material->createClone());
				layerOverlayMaterial->setEmissive(layerOverlayColor);
				layerOverlayMaterial->setDiffuse(layerOverlayColor);
				layerOverlayMaterial->setAmbient(layerOverlayColor);
				layerOverlayMaterial->setAlpha(1.0f);
			}
			return layerOverlayMaterial;
		}

		NI::Pointer<NI::AlphaProperty> getLayerAlphaProperty() {
			if (!layerAlphaProperty) {
				layerAlphaProperty = new NI::AlphaProperty();
				layerAlphaProperty->flags = 3821;
				layerAlphaProperty->alphaTestRef = 255;
			}
			return layerAlphaProperty;
		}

		NI::Pointer<NI::VertexColorProperty> getLayerVertexColorProperty() {
			if (!layerVertexColorProperty) {
				layerVertexColorProperty = new NI::VertexColorProperty();
			}
			return layerVertexColorProperty;
		}

		NodeColorData* getNodeColorData(NI::TriShape* node) {
			auto it = nodeMaterialData.find(node);
			if (it != nodeMaterialData.end()) {
				return it->second;
			}
			else {
				auto newData = new NodeColorData();
				nodeMaterialData[node] = newData;
				return newData;
			}
		}

		// TODO: Stale references might accumulate if we reload the cell
		// and CS actually creates new TriShape instances,
		// however they will never be accessed, so no crashing should occur
		void removeNodeColorData(NI::TriShape* node) {
			auto it = nodeMaterialData.find(node);
			if (it != nodeMaterialData.end()) {
				delete it->second;
				nodeMaterialData.erase(it);
			}
		}

		void removeObject(Reference* objRef);

		void addObject(Reference* objRef);

		void updateObject(Reference* objRef, bool forceRestore = false);

		void refreshObjects();

		void moveObjectToLayer(Reference* objRef, LayerData* currentLayerInput = nullptr);

		void moveSelectionToLayer();

		void clearLayer();

		size_t get_counts() {
			size_t total = 0;
			for (auto& cell_data : perCellReferences) {
				total += cell_data.second.size();
			}
			return total;
		}

		void selectObjects() {}       // Dummy selection

		void debugPrint();
	};

	void createLayersWindow();
	void toggleLayersWindow(bool show);

	void forceToggleLayersWindow(HMENU viewMenu);
	void refreshLayersMenuItem(HMENU viewMenu);
	bool IsRenderWindowVisible(HMENU viewMenu);

	std::unordered_map<size_t, LayerData*> GetLayers();
	LayerData* getLayerById(size_t id);
	LayerData* getLayerByObject(Reference* obj);

	extern HWND hLayersWnd;

	const std::string LAYER_CONFIG_PATH = "csse_layers.toml";

	void saveLayersToToml();
	void loadLayersFromToml();
}