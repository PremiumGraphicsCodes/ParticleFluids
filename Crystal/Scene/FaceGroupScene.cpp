#include "FaceGroupScene.h"

#include "PolygonMeshScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"


#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel FaceGroupScene::toViewModel() const
{
	return SceneViewModel();
	/*
	if (!isVisible()) {
		return;
	}

	TriangleBuffer bf(*getShape());
	for (const auto& group : getShape()->getGroups()) {
		auto materialId = group.attributeId;
		auto parent = getParent();
		if (parent != nullptr) {
			auto mat = static_cast<MaterialScene*>(parent->findSceneById(materialId));
			if (mat == nullptr) {
				bf.add(group, Material());
			}
			else {
				bf.add(group, *(mat->getMaterial()));
			}
		}
		else {
			bf.add(group, Material());
		}
	}
	viewModel.triangleBuffers.push_back(bf);
	*/
}
