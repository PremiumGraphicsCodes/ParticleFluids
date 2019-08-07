#include "PolygonMeshScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"


#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/DrawableId.h"

#include "LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SceneViewModel PolygonMeshScene::toViewModel() const
{
	SceneViewModel viewModel;
	if (!isVisible()) {
		return viewModel;
	}

	auto lights = getParent()->findScenes(SceneType::LightScene);
	PointLight light;
	if(!lights.empty()) {
		light = static_cast<LightScene*>(lights.front())->getLight();
	}

	// Polygon直下にあるfaceはデフォルトで描画．
	TriangleBuffer bf(*getShape());
	auto materialScene = static_cast<MaterialScene*>(getParent()->findSceneByName(materialName));
	if(materialScene == nullptr) {
		bf.add(getShape()->getFaces(), 0);
	}
	else {
		bf.add(getShape()->getFaces(), 0);
	}

	viewModel.triangleBuffers.push_back(bf);
	return viewModel;
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
