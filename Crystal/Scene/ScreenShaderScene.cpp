#include "ScreenShaderScene.h"

#include "../Shader/GLObjectFactory.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"
#include "TextureScene.h"
#include "LightScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool ScreenShaderScene::build(GLObjectFactory& factory)
{
	if (!pointRenderer.build()) {
		return false;
	}
	if (!wireRenderer.build()) {
		return false;
	}
	if (!smoothRenderer.build()) {
		return false;
	}

	texture = factory.getTextureFactory()->createTextureObject("Scene",Image(512, 512));
	//texture.create(, 1);
	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);
	return true;
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

void ScreenShaderScene::render(Camera* camera, const ScreenShaderBuffer& buffer)
{
	this->camera = camera;
	frameBufferObject->setTexture(texture);
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture.getWidth(), texture.getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mask.showPoints) {
		for (auto buffer : buffer.pointBuffers) {
			buffer.camera = *camera;
			pointRenderer.send(buffer);
			pointRenderer.render();
		}
	}
	if (mask.showLines) {
		for (auto lb : buffer.lineBuffers) {
			lb.camera = *camera;
			wireRenderer.setBuffer(lb);
			wireRenderer.render();
		}
	}
	if (mask.showTrianlges) {
		std::vector<Material> mBuffer;
		for (auto m : buffer.materialScenes) {
			mBuffer.push_back(*m->getMaterial());
		}
		smoothRenderer.send(mBuffer);
		LightShaderBuffer lBuffer;
		for (auto l : buffer.lightScenes) {
			lBuffer.add(*l->getLight());
		}
		TextureShaderBuffer texBuffer;
		for (auto tex : buffer.textureScenes) {
			texBuffer.add(tex->getTextureObject());
		}
		for (auto pm : buffer.pmScenes) {
	//		smoothRenderer.send();
			smoothRenderer.render();
		}
	}
	//texture.unbind();
	frameBufferObject->unbind();
}