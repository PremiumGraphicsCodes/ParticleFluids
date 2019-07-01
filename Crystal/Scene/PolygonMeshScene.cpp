#include "PolygonMeshScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"


#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

void PolygonMeshScene::addViewModel(Crystal::UI::SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}

	TriangleBuffer bf(*getShape());
	for (const auto& group : getShape()->getGroups()) {
		auto mat = getMaterial();
		bf.add(group, Material());
		/*
		if (mat == nullptr) {
			bf.add(group, Material());
		}
		else {
			bf.add(group, *(mat->getMaterial()));
		}
		*/
	}
	viewModel.triangleBuffers.push_back(bf);
}

void PolygonMeshScene::addViewModel(Crystal::UI::SceneIdViewModel& viewModel) const
{
	const auto objectId = getId();
	const auto& faces = getShape()->getFaces();
	int childId = 0;
	int index = 0;
	for (auto f : faces) {
		Graphics::DrawableID did(objectId, childId++);
		const auto& idColor = did.toColor();
		viewModel.triangleIdBuffer.add(f->getV1()->getPosition(), idColor, index++);
		viewModel.triangleIdBuffer.add(f->getV2()->getPosition(), idColor, index++);
		viewModel.triangleIdBuffer.add(f->getV3()->getPosition(), idColor, index++);
	}
}

void PolygonMeshScene::getBoundingBox(Crystal::Math::Box3d& boundingBox) const
{
	boundingBox.add(getShape()->getBoundingBox());
}
