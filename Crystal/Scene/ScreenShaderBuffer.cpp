#include "ScreenShaderBuffer.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

void ScreenShaderBuffer::release()
{
	for (auto& pb : pointBuffers) {
		pb.release();
	}
	pointBuffers.clear();
	for (auto& lb : lineBuffers) {
		lb.release();
	}
	lineBuffers.clear();
	for (auto& pm : pmScenes) {
		pm.release();
	}
	pmScenes.clear();

	textureScenes.clear();
	materialScenes.clear();
	lightScenes.clear();
}

void ScreenShaderBuffer::add(ParticleSystemScene* scene)
{
	const auto& ps = scene->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	pb.setMatrix(scene->getMatrix());

	PointShaderBuffer buffer;
	buffer.build();
	buffer.send(pb);
	pointBuffers.push_back(buffer);
}

void ScreenShaderBuffer::add(WireFrameScene* scene)
{
	const auto& shape = scene->getShape();
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	const auto& color = scene->getAttribute().color;
	LineBuffer buffer(scene->getAttribute().width);
	buffer.setMatrix(scene->getMatrix());
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}
	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	LineShaderBuffer lb;
	lb.build();
	lb.send(buffer);
	lineBuffers.push_back(lb);
}

void ScreenShaderBuffer::add(PolygonMeshScene* parent)
{
	const auto& shape = parent->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();
	const auto& matrix = parent->getMatrix();

	for (auto child : parent->getChildren()) {
		int materialId = 0;
		auto scene = static_cast<FaceGroupScene*>(child);
		if (scene->getMaterial() != nullptr) {
			materialId = scene->getMaterial()->getMaterialId();
		}

		auto faces = scene->getFaces();
		{
			SmoothBuffer buffer;
			buffer.setMatrix(matrix);
			for (const auto& f : faces) {
				const auto& vIds = f.getVertexIds();
				for (const auto vId : vIds) {
					const auto& v = vs[vId];
					const auto& p = ps[v.positionId];
					const auto& n = ns[v.normalId];
					Math::Vector2df texCoord(0, 0);
					if (v.texCoordId != -1) {
						texCoord = tcs[v.texCoordId];
					}
					buffer.addVertex(p, n, texCoord, materialId);
				}
			}
			SmoothShaderBuffer glBuffer;
			glBuffer.build();
			glBuffer.send(buffer);
			pmScenes.push_back(glBuffer);
		}
	}
}
