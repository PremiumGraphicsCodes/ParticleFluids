#include "WireFrameController.h"

#include "WireFrameScene.h"
#include "LineBuffer.h"

#include "LineShaderScene.h"
#include "SceneShader.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

WireFrameController::WireFrameController(WireFrameScene* model) :
	model(model),
	view(nullptr),
	parentIdView(nullptr)
{
}

void WireFrameController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->view->build(glFactory);
		sceneShader->getScene()->screen.add(this->view);
	}
	{
		this->parentIdView = new LineShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->parentIdView->build(glFactory);
		sceneShader->getScene()->parentId.add(this->parentIdView);
	}

	updateView();
}

void WireFrameController::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void WireFrameController::updateScreenView()
{
	const auto& color = model->getAttribute().color;

	const auto& shape = model->getShape();
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	LineBuffer buffer(model->getAttribute().width);
	buffer.setMatrix(model->getMatrix());
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}
	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	this->view->send(buffer);
}

void WireFrameController::updateParentIdView()
{
	const auto objectId = model->getId();

	const auto& shape = model->getShape();
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	DrawableID did(objectId);
	const auto color = did.toColor();
	LineBuffer buffer(model->getAttribute().width);
	buffer.setMatrix(model->getMatrix());
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}

	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	this->parentIdView->send(buffer);
}

void WireFrameController::updateChildIdView()
{

}

