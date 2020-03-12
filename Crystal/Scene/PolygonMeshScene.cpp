#include "PolygonMeshScene.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"
#include "../Math/Line3d.h"

#include "LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

PolygonMeshScene::PolygonMeshScene() :
	IShapeScene(-1, nullptr),
	shape(nullptr)
{}

PolygonMeshScene::PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<PolygonMesh> shape) :
	IShapeScene(id, name, shape.get()),
	shape(std::move(shape))
{}

void PolygonMeshScene::onSend()
{
	if (!isVisible()) {
		return;
	}

	const auto& faces = shape->getFaces();
	const auto& vertices = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& ns = shape->getNormals();
	const auto& tcs = shape->getTexCoords();

	for (auto g : groups) {
		g->send();
	}
	/*
	SmoothTriangleBuffer buffer;
	for (const auto& f : faces) {
		const auto& vIds = f.getVertexIds();
		for(const auto vId : vIds) {
			const auto& v = vertices[vId];
			const auto& p = ps[v.positionId];
			const auto& n = ns[v.normalId];
			Math::Vector2df texCoord(0, 0);
			if (v.texCoordId != -1) {
				texCoord = tcs[v.texCoordId];
			}
			buffer.addVertex(p, n, texCoord, f.materialId);
		}
	}
	viewModel.triangleBuffers.push_back(buffer);
	*/
}

void PolygonMeshScene::send(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const
{
	const auto objectId = getId();
	const auto& vertices = getShape()->getVertices();
	const auto& positions = getShape()->getPositions();
	const auto& faces = getShape()->getFaces();
	int childId = 0;
	int index = 0;

	LineBuffer buffer;
	buffer.setMatrix(getMatrix());
	for (auto f : faces) {
		Graphics::DrawableID parentDid(objectId);
		Graphics::DrawableID childDid(childId++);
		const auto& idColor = parentDid.toColor();
		const auto& vIds = f.getVertexIds();

		buffer.addVertex( positions[ vertices[vIds[0]].positionId ], idColor);
		buffer.addVertex( positions[ vertices[vIds[1]].positionId ], idColor);
		buffer.addVertex( positions[ vertices[vIds[2]].positionId ], idColor);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
	}
	parentIdViewModel.triangleIdBuffers.push_back(buffer);
}

Box3d PolygonMeshScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}

Vector3dd PolygonMeshScene::getPosition(const int index) const
{
	const auto& positions = getShape()->getPositions();
	return positions[index];
}

IShapeScene* PolygonMeshScene::clone() const
{
	return nullptr;
}

void PolygonMeshScene::onRender(SceneRenderer* renderer)
{
	for (auto group : groups) {
		group->render(renderer);
	}
}