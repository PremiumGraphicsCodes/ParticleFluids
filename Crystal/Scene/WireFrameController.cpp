#include "WireFrameController.h"

#include "WireFrameScene.h"
#include "LineBuffer.h"

using namespace Crystal::Scene;

WireFrameController::WireFrameController(WireFrameScene* model) :
	model(model)
{
}

void WireFrameController::createView(LineShader* renderer)
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
	/*
	LineShaderScene lb;
	lb.build(glFactory);
	lb.send(buffer);
	lineBuffers.push_back(lb);
	*/
}

void WireFrameController::updateView()
{

}
