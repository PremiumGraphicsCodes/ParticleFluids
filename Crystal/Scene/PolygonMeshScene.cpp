#include "PolygonMeshScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

#include "LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void PolygonMeshScene::toViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}

	// Polygon直下にあるfaceはデフォルトで描画．
	SmoothTriangleBuffer bf(*getShape());
	bf.add(getShape()->getFaces(), 0);

	viewModel.triangleBuffers.push_back(bf);
}

SceneIdViewModel PolygonMeshScene::toIdViewModel() const
{
	SceneIdViewModel viewModel;
	const auto objectId = getId();
	const auto& vertices = getShape()->getVertices();
	const auto& positions = getShape()->getPositions();
	const auto& faces = getShape()->getFaces();
	int childId = 0;
	int index = 0;
	for (auto f : faces) {
		Graphics::DrawableID did(objectId, childId++);
		const auto& idColor = did.toColor();
		viewModel.triangleIdBuffer.add( positions[ vertices[f.v1].positionId ], idColor, index++);
		viewModel.triangleIdBuffer.add( positions[ vertices[f.v2].positionId ], idColor, index++);
		viewModel.triangleIdBuffer.add( positions[ vertices[f.v3].positionId ], idColor, index++);
	}
	return viewModel;
}

void PolygonMeshScene::getBoundingBox(Crystal::Math::Box3d& boundingBox) const
{
	boundingBox.add(getShape()->getBoundingBox());
}

Vector3dd PolygonMeshScene::getPosition(const int index) const
{
	const auto& positions = getShape()->getPositions();
	return positions[index];
}
