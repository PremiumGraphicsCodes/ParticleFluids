#include "PointShaderScene.h"

#include "PointShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void PointShaderScene::build()
{
	vbo.position.build();
	vbo.size.build();
	vbo.color.build();

	//vao.build();
}

void PointShaderScene::release()
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
