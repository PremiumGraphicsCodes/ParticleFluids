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

	{
		const auto& vertices = shape->getVertices();
		const auto& ps = shape->getPositions();
		const auto& ns = shape->getNormals();
		const auto& tcs = shape->getTexCoords();

		SmoothTriangleBuffer buffer;
		for (auto v : vertices) {
			const auto& p = ps[v.positionId];
			const auto& n = ns[v.normalId];
			Math::Vector2df texCoord(0,0);
			if (v.texCoordId != -1) {
				texCoord = tcs[v.texCoordId];
			}
			buffer.addVertex(p, n, texCoord);
		}

		SmoothFaceGroupBuffer groupBuffer(0);
		const auto& faces = shape->getFaces();
		for (auto f : faces) {
			groupBuffer.addFace(f.v1, f.v2, f.v3);
		}
		buffer.addGroup(groupBuffer);

		viewModel.triangleBuffers.push_back(buffer);
	}
	if (isSelected()) {
		LineBuffer buffer;
	}
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
		buffer.addVertex( positions[ vertices[f.v1].positionId ], idColor);
		buffer.addVertex( positions[ vertices[f.v2].positionId ], idColor);
		buffer.addVertex( positions[ vertices[f.v3].positionId ], idColor);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
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
