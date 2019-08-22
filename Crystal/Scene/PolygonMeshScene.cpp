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

	SmoothTriangleBuffer bf(*getShape());
	bf.add(getShape()->getFaces(), 0);

	viewModel.triangleBuffers.push_back(bf);
}

void PolygonMeshScene::toIdViewModel(SceneIdViewModel& viewModel) const
{
	const auto objectId = getId();
	const auto& vertices = getShape()->getVertices();
	const auto& positions = getShape()->getPositions();
	const auto& faces = getShape()->getFaces();
	int childId = 0;
	int index = 0;

	LineBuffer buffer;
	for (auto f : faces) {
		Graphics::DrawableID did(objectId, childId++);
		const auto& idColor = did.toColor();
		buffer.add( positions[ vertices[f.v1].positionId ], idColor, index++);
		buffer.add( positions[ vertices[f.v2].positionId ], idColor, index++);
		buffer.add( positions[ vertices[f.v3].positionId ], idColor, index++);
	}
	viewModel.triangleIdBuffers.push_back(buffer);
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
