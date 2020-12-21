#include "PMAsWFPresenter.h"

#include "PolygonMeshScene.h"

#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

PMAsWFPresenter::PMAsWFPresenter(PolygonMeshScene* model) :
	IPolygonMeshPresenter(model),
	view(nullptr)
{
}

void PMAsWFPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	/*
	{
		this->parentIdView = new LineShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->parentIdView->build(glFactory);
		sceneShader->getScene()->parentId.add(this->parentIdView);
	}
	*/

	updateView();

}

void PMAsWFPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	this->view->release(glFactory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	/*
	this->parentIdView->release(glFactory);
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;
	*/
}

void PMAsWFPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PMAsWFPresenter::updateScreenView()
{
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();

	auto faces = shape->getFaces();

	LineBuffer buffer;
	for (const auto& p : ps) {
		buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
	}

	auto groups = model->getGroups();
	for (const auto& scene : groups) {
		int materialId = 0;
		auto faces = shape->getFaces();
		for (const auto& f : faces) {
			const auto& vIds = f.getVertexIds();
			for (const auto vId : vIds) {
				auto vIndex = vs[vId];
				buffer.addIndex(vIndex.positionId);
			}
		}
	}
	this->view->send(buffer);
}

void PMAsWFPresenter::updateParentIdView()
{

}

void PMAsWFPresenter::updateChildIdView()
{

}
