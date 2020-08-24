#include "TriangleShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

void TriangleShaderScene::build()
{
	vbo.position.build();
	vbo.color.build();
}

void TriangleShaderScene::release()
{
	vbo.position.release();
	vbo.color.release();
}

void TriangleShaderScene::send(const LineBuffer& buffer)
{
	vbo.position.send(buffer.getPositions().get());
	vbo.color.send(buffer.getColors().get());

	indices = buffer.getIndices().get();
}
