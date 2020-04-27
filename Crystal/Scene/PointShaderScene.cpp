#include "PointShaderScene.h"

#include "PointShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

PointShaderScene::PointShaderScene(const std::string& name) :
	IShaderScene(name),
	shader(nullptr),
	camera(nullptr)
{}

bool PointShaderScene::build(GLObjectFactory& glFactory)
{
	vbo.position.build();
	vbo.size.build();
	vbo.color.build();

	//vao.build();
	return true;
}

void PointShaderScene::release(GLObjectFactory& glFactory)
{
	vbo.position.release();
	vbo.size.release();
	vbo.color.release();

	//vao.release();
}

void PointShaderScene::send(const PointBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& colors = buffer.getColor().get();
	const auto& sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	//vao.bind();
	vbo.position.send(positions);
	vbo.size.send(sizes);
	vbo.color.send(colors);
	//vao.unbind();

	count = positions.size() / 3;
	matrix = buffer.getMatrix();
}

void PointShaderScene::render()
{
	shader->send(*this);
	shader->render();
}

void PointShaderScene::setShader(PointShader* shader)
{
	this->shader = shader;
}
