#include "TriangleShaderScene.h"

#include "TriangleShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool TriangleShaderScene::build(GLObjectFactory& glFactory)
{
	vbo.position.build();
	vbo.color.build();
	return true;
}

void TriangleShaderScene::release(GLObjectFactory& glFactory)
{
	vbo.position.release();
	vbo.color.release();
}

void TriangleShaderScene::send(const TriangleBuffer& buffer)
{
	vbo.position.send(buffer.getPositions().get());
	vbo.color.send(buffer.getColors().get());

	indices = buffer.getIndices().get();
}

void TriangleShaderScene::render()
{
	shader->setScene(this);
	shader->render();
}

void TriangleShaderScene::setShader(TriangleShader* shader)
{
	this->shader = shader;
}
