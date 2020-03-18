#include "LineShaderBuffer.h"

using namespace Crystal::Scene;

void LineShaderBuffer::build()
{
	vbo.position.build();
	vbo.color.build();

	//vao.build();
}

void LineShaderBuffer::release()
{
	vbo.position.release();
	vbo.color.release();

	//vao.release();
}

void LineShaderBuffer::send(const LineBuffer& buffer)
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
