
#include "LineShaderScene.h"

using namespace Crystal::Scene;

void LineShaderScene::build()
{
	vbo.position.build();
	vbo.color.build();

	//vao.build();
}

void LineShaderScene::release()
{
	vbo.position.release();
	vbo.color.release();

	//vao.release();
}

void LineShaderScene::send(const LineBuffer& buffer)
{
	const auto positions = buffer.getPositions().get();
	const auto colors = buffer.getColors().get();
	if (positions.empty()) {
		return;
	}

	vbo.position.send(positions);
	vbo.color.send(colors);

	indices = buffer.getIndices().get();
	matrix = buffer.getMatrix();
	lineWidth = buffer.getWidth();
}
