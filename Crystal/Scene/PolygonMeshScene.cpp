#include "PolygonMeshScene.h"

#include "../Graphics/TriangleBuffer.h"
#include "SceneViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

void PolygonMeshScene::addViewModel(Crystal::UI::SceneViewModel& viewModel)
{
	if (!isVisible()) {
		return;
	}

	TriangleBuffer bf(*getShape());
	for (const auto& group : getShape()->getGroups()) {
		auto mat = getMaterial();
		if (mat == nullptr) {
			bf.add(group, Material());
		}
		else {
			bf.add(group, *(mat->getMaterial()));
		}
	}
	viewModel.triangleBuffers.push_back(bf);

	/*
	const auto& vertices =  object.getShape()->getVertices();
	for (auto l : vertices) {
		triangleBuffer.add(*object.getShape());
	}
	*/
}

