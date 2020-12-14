#include "PMToWFPresenter.h"

#include "PolygonMeshScene.h"

#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

PMToWFPresenter::PMToWFPresenter(PolygonMeshScene* model) :
	model(model),
	view(nullptr)
{
}

void PMToWFPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
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

void PMToWFPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PMToWFPresenter::updateScreenView()
{
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();

	//for (auto child : model->getChildren()) {
		auto faces = shape->getFaces();

		LineBuffer buffer;
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
				buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
			}
		}
		this->view->send(buffer);
	//}
}

void PMToWFPresenter::updateParentIdView()
{

}

void PMToWFPresenter::updateChildIdView()
{

}
