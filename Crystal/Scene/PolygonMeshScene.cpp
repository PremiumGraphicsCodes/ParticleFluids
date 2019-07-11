#include "PolygonMeshScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"


#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/DrawableId.h"
#include "FaceGroupScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void PolygonMeshScene::addViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}

	// Polygon直下にあるfaceはデフォルトで描画．
	TriangleBuffer bf(*getShape());
	bf.add(getShape()->getFaces(), Material());

	// groupにあるfaceは対応するmaterialで描画．
	const auto& children = getChildren();
	for (auto& child : children) {
		auto faceGroup = static_cast<FaceGroupScene*>(child);
		auto materialScene = static_cast<MaterialScene*>( getParent()->findSceneByName( faceGroup->getMaterialName() ) );
		bf.add(faceGroup->getShape(), *(materialScene->getMaterial()));
	}
	viewModel.triangleBuffers.push_back(bf);
}

void PolygonMeshScene::addViewModel(SceneIdViewModel& viewModel) const
{
	const auto objectId = getId();
	const auto& vertices = getShape()->getVertices();
	const auto& faces = getShape()->getFaces();
	int childId = 0;
	int index = 0;
	for (auto f : faces) {
		Graphics::DrawableID did(objectId, childId++);
		const auto& idColor = did.toColor();
		viewModel.triangleIdBuffer.add( vertices[f.v1]->getPosition(), idColor, index++);
		viewModel.triangleIdBuffer.add( vertices[f.v2]->getPosition(), idColor, index++);
		viewModel.triangleIdBuffer.add( vertices[f.v3]->getPosition(), idColor, index++);
	}
}

void PolygonMeshScene::getBoundingBox(Crystal::Math::Box3d& boundingBox) const
{
	boundingBox.add(getShape()->getBoundingBox());
}
