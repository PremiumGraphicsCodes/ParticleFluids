#include "PolygonMeshScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"


#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void PolygonMeshScene::addViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}

	TriangleBuffer bf(*getShape());
	for (const auto& group : getShape()->getGroups()) {
		auto materialId = group.attributeId;
		auto parent = getParent();
		if (parent != nullptr) {
			auto mat = static_cast<MaterialScene*>( parent->findSceneById(materialId) );
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
}

void PolygonMeshScene::addViewModel(SceneIdViewModel& viewModel) const
{
	const auto objectId = getId();
	const auto& vertices = getShape()->getVertices();
	const auto& groups = getShape()->getGroups();
	int childId = 0;
	int index = 0;
	for (auto g : groups) {
		const auto& faces = g.faces;
		for (auto f : faces) {
			Graphics::DrawableID did(objectId, childId++);
			const auto& idColor = did.toColor();
			viewModel.triangleIdBuffer.add( vertices[f.v1]->getPosition(), idColor, index++);
			viewModel.triangleIdBuffer.add( vertices[f.v2]->getPosition(), idColor, index++);
			viewModel.triangleIdBuffer.add( vertices[f.v3]->getPosition(), idColor, index++);
		}
	}
}

void PolygonMeshScene::getBoundingBox(Crystal::Math::Box3d& boundingBox) const
{
	boundingBox.add(getShape()->getBoundingBox());
}
