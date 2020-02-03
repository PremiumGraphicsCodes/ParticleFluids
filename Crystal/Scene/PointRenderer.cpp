#include "PointRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;


PointRenderer::PointRenderer() :
	count(0)
{
}

bool PointRenderer::build(GLObjectFactory& factory)
{
	setVertexShaderSource(getBuiltInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");

	addAttribute("position");
	addAttribute("color");
	addAttribute("pointSize");

	vertex_vbo.build();
	size_vbo.build();
	color_vbo.build();
	glGenVertexArrays(1, &vao);

	return build_(factory);
}

void PointRenderer::send(const PointBuffer& buffer)
{
	auto shader = getShader();

	this->buffer = buffer;

	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	vertex_vbo.send(positions);
	size_vbo.send(sizes);
	color_vbo.send(colors);

	glBindVertexArray(vao);

	{
		vertex_vbo.bind();
		auto location = shader->getAttribLocation("position");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		vertex_vbo.unbind();
	}

	{
		size_vbo.bind();
		auto location = shader->getAttribLocation("pointSize");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (GLvoid*)0);
		size_vbo.unbind();
	}

	{
		glBindBuffer(GL_ARRAY_BUFFER, color_vbo.getHandle()); //以下よりcolor_vboでバインドされているバッファが処理される
		auto location = shader->getAttribLocation("color");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(0);

	this->count = positions.size() / 3;
}

void PointRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	/*
	if (count == 0) {
		return;
	}
	*/

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto modelviewMatrix = camera.getModelViewMatrix() * Matrix4df(buffer.getMatrix());

	shader->bind();

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	glBindVertexArray(vao);
	shader->drawPoints(count);
	glBindVertexArray(0);

	shader->bindOutput("fragColor");

	shader->disablePointSprite();
	shader->disableDepthTest();

	shader->unbind();
}

std::string PointRenderer::getBuiltInVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vColor = color;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string PointRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec2 coord = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = 1.0 - dot(coord, coord);" << std::endl
		<< "	if (distSquared < 0.0) {" << std::endl
		<< "		discard;" << std::endl
		<< "	}" << std::endl
		<< "	fragColor.rgba = vColor;" << std::endl
		//		<< "	fragColor.a = sqrt(distSquared) * vColor.a;" << std::endl
		//		<< "	fragColor.a = 0.1;//sqrt(distSquared);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}