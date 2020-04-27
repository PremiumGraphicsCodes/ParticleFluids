#include "ScreenIdShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Scene;

ScreenIdShaderScene::ScreenIdShaderScene(const std::string& name) :
	IShaderScene(name)
{
}

void ScreenIdShaderScene::render()
{
	const auto& children = getChildren();
	for (auto c : children) {
		c->render();
	}
}


void ScreenIdShaderScene::add(PointShaderScene* scene)
{
	scene->setCamera(camera);
	this->pointScenes.push_back(scene);
	addChild(scene);
}

void ScreenIdShaderScene::add(WireFrameScene* scene)
{
	const auto objectId = scene->getId();
	int childId = 0;
	int index = 0;

	const auto& positions = scene->getShape()->getPositions();
	LineBuffer lineBuffer(scene->getAttribute().width);
	lineBuffer.setMatrix(scene->getMatrix());
	for (const auto& l : positions) {
		Graphics::DrawableID parentDid(objectId);
		Graphics::DrawableID childDid(childId++);
		lineBuffer.addVertex(l, parentDid.toColor());
		lineBuffer.addIndex(index++);
	}
	//parentIdViewModel.lineIdBuffers.push_back(lineBuffer);
}

void ScreenIdShaderScene::add(PolygonMeshScene* scene)
{
	const auto objectId = scene->getId();
	const auto& vertices = scene->getShape()->getVertices();
	const auto& positions = scene->getShape()->getPositions();
	const auto& faces = scene->getShape()->getFaces();
	int childId = 0;
	int index = 0;

	LineBuffer buffer;
	buffer.setMatrix(scene->getMatrix());
	for (auto f : faces) {
		Graphics::DrawableID parentDid(objectId);
		Graphics::DrawableID childDid(childId++);
		const auto& idColor = parentDid.toColor();
		const auto& vIds = f.getVertexIds();

		buffer.addVertex(positions[vertices[vIds[0]].positionId], idColor);
		buffer.addVertex(positions[vertices[vIds[1]].positionId], idColor);
		buffer.addVertex(positions[vertices[vIds[2]].positionId], idColor);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
		buffer.addIndex(index++);
	}
	//parentIdViewModel.triangleIdBuffers.push_back(buffer);

}

void ScreenIdShaderScene::setCamera(CameraShaderScene* camera)
{
	this->camera = camera;
}
