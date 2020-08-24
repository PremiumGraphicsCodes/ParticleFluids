#include "PolygonMeshPresenter.h"

#include "PolygonMeshScene.h"

#include "SceneShader.h"

#include "../Graphics/DrawableId.h"
#include "../Scene/TriangleShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

PolygonMeshPresenter::PolygonMeshPresenter(PolygonMeshScene* model) :
	model(model),
	view(nullptr)
{
}

void PolygonMeshPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new SmoothShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getSmoothShader());
		this->view->build(glFactory);
		sceneShader->getScene()->screen.add(this->view);
	}
	/*
	{
		this->parentIdView = new TriangleShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->parentIdView->build(glFactory);
		sceneShader->getScene()->parentId.add(this->parentIdView);
	}
	*/

	updateView();
}

void PolygonMeshPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PolygonMeshPresenter::updateScreenView()
{
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();
	const auto& matrix = model->getMatrix();

	SmoothBuffer buffer;
	buffer.setMatrix(matrix);

	for (auto child : model->getChildren()) {
		int materialId = 0;
		auto scene = static_cast<FaceGroupScene*>(child);
		/*
		if (scene->getMaterial() != nullptr) {
			materialId = scene->getMaterial()->getMaterialId();
		}
		*/

		auto faces = scene->getFaces();
		{
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
			//SmoothShaderScene* glBuffer = new SmoothShaderScene("");
			//glBuffer->setShader(sceneShader->getObjectRenderer()->getSmoothShader());
			//glBuffer->build(glFactory);
			//glBuffer->send(buffer);
			//sceneShader->getScene()->screen.add(glBuffer);
		}
	}
	this->view->send(buffer);

}

void PolygonMeshPresenter::updateParentIdView()
{
	LineBuffer parentIdBuffer;
	parentIdBuffer.setMatrix(model->getMatrix());

	const auto& vs = model->getShape()->getVertices();
	const auto& ps = model->getShape()->getPositions();

	const auto objectId = model->getId();

	for (auto child : model->getChildren()) {
		auto scene = static_cast<FaceGroupScene*>(child);

		auto faces = scene->getFaces();
		for (const auto& f : faces) {
			const auto& vIds = f.getVertexIds();
			for (const auto vId : vIds) {
				const auto& v = vs[vId];
				const auto& p = ps[v.positionId];
				DrawableID parentDid(objectId);
				//parentIdBuffer.add(p, n, texCoord, materialId);
			}
		}

		/*
		const auto objectId = model->getId();
		const auto& particles = model->getShape()->getParticles();
		int particleId = 0;
		for (auto p : particles) {
			DrawableID parentDid(objectId);
			parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
		}
		*/
	}
	//parentIdView->send(parentIdBuffer);

}

void PolygonMeshPresenter::updateChildIdView()
{

}
