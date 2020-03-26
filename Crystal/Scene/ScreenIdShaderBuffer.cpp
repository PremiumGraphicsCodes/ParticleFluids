#include "ScreenIdShaderBuffer.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Scene;

void ScreenIdShaderBuffer::add(ParticleSystemScene* scene)
{
	const auto objectId = scene->getId();
	const auto& particles = scene->getShape()->getParticles();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	parentIdBuffer.setMatrix(scene->getMatrix());
	PointBuffer childIdBuffer;
	childIdBuffer.setMatrix(scene->getMatrix());
	for (auto p : particles) {
		Graphics::DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
		Graphics::DrawableID childDid(particleId++);
		childIdBuffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	//parentIdViewModel.pointIdBuffers.push_back(parentIdBuffer);
	//childIdViewModel.pointIdBuffers.push_back(childIdBuffer);

}

void ScreenIdShaderBuffer::add(WireFrameScene* scene)
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

void ScreenIdShaderBuffer::add(PolygonMeshScene* scene)
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