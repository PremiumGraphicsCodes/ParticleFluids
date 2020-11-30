#include "SolidAsWFPresenter.h"

#include "SolidScene.h"
#include "LineBuffer.h"

#include "LineShaderScene.h"
#include "SceneShader.h"

#include "../Shape/WireFrameBuilder.h"

//#include "../Graphics/DrawableId.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Shape;

SolidAsWFPresenter::SolidAsWFPresenter(SolidScene* model) :
	model(model),
	view(nullptr)
{
}

void SolidAsWFPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();
}

void SolidAsWFPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void SolidAsWFPresenter::updateScreenView()
{
	const auto& color = model->getColor();

	const auto& shape = model->getBoundingBox();

	WireFrameBuilder builder;
	builder.build(shape);
	const auto& positions = builder.getPositions();
	const auto& edges = builder.getEdges();

	LineBuffer buffer(1.0f);
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}
	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}
	this->view->send(buffer);
}

void SolidAsWFPresenter::updateParentIdView()
{
}

void SolidAsWFPresenter::updateChildIdView()
{

}