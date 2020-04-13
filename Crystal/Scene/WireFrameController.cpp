#include "WireFrameController.h"

#include "WireFrameScene.h"
#include "LineBuffer.h"

#include "LineShaderScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

WireFrameController::WireFrameController(WireFrameScene* model) :
	model(model)
{
}

void WireFrameController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	const auto& shape = model->getShape();
	const auto& positions = shape->getPositions();
	const auto& edges = shape->getEdges();

	const auto& color = model->getAttribute().color;
	LineBuffer buffer(model->getAttribute().width);
	buffer.setMatrix(model->getMatrix());
	for (const auto& l : positions) {
		buffer.addVertex(l, color);
	}
	for (const auto& e : edges) {
		buffer.addIndex(e.originId);
		buffer.addIndex(e.destId);
	}

	view = new LineShaderScene();
	view->setShader(sceneShader->getObjectRenderer()->getWireShader());
	//view->camera = *(sceneShader->getCamera());
	view->build(glFactory);
	view->send(buffer);
	sceneShader->getBuffer()->screen.lineBuffers.push_back(*view);
}

void WireFrameController::updateView()
{

}
