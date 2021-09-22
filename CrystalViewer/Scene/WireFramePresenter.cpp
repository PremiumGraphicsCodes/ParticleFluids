#include "WireFramePresenter.h"

#include "WireFrameScene.h"
#include "LineBuffer.h"

#include "LineShaderScene.h"
#include "SceneShader.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

WireFramePresenter::WireFramePresenter(WireFrameScene* model) :
	IWireFramePresenter(model),
	view(nullptr),
	parentIdView(nullptr)
{
}

void WireFramePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}
	{
		this->parentIdView = new LineShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->parentIdView->build(glFactory);
		sceneShader->getParentIdRenderer()->addScene(this->parentIdView);
	}

	updateView();
}

void WireFramePresenter::removeView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	this->view->release(glFactory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;

	this->parentIdView->release(glFactory);
	sceneShader->getParentIdRenderer()->removeScene(this->parentIdView);
	delete this->parentIdView;
}

void WireFramePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void WireFramePresenter::updateScreenView()
{
	const auto& color = model->getAttribute().color;

	const auto& shape = model->getShape();
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	LineBuffer buffer(model->getAttribute().width);
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}
	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	this->view->send(buffer);
}

void WireFramePresenter::updateParentIdView()
{
	const auto objectId = model->getId();

	const auto& shape = model->getShape();
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	DrawableID did(objectId);
	const auto color = did.toColor();
	LineBuffer buffer(model->getAttribute().width);
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}

	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	this->parentIdView->send(buffer);
}

void WireFramePresenter::updateChildIdView()
{

}

