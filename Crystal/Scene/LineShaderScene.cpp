
#include "LineShaderScene.h"

#include "LineShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

LineShaderScene::LineShaderScene(const std::string& name) :
	IShaderScene(name),
	shader(nullptr)
{}

bool LineShaderScene::build(GLObjectFactory& glFactory)
{
	vbo.position.build();
	vbo.color.build();

	//vao.build();
	return true;
}

void LineShaderScene::release(GLObjectFactory& glFactory)
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

void LineShaderScene::render()
{
	shader->setScene(this);
	shader->render();
}