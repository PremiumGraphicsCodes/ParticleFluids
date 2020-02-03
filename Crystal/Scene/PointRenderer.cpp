#include "PointRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

PointRenderer::PointRenderer()
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

	glGenBuffers(1, &vertex_vbo);
	glGenBuffers(1, &size_vbo);
	glGenBuffers(1, &color_vbo);
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

	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //GLコンテキストにvertex_vboをGL_ARRAY_BUFFERでバインド。
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), positions.data(), GL_STATIC_DRAW); //実データを格納

	glBindBuffer(GL_ARRAY_BUFFER, size_vbo); //GLコンテキストにvertex_vboをGL_ARRAY_BUFFERでバインド。
	glBufferData(GL_ARRAY_BUFFER, sizeof(sizes[0]) * sizes.size(), sizes.data(), GL_STATIC_DRAW); //実データを格納

	glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //GLコンテキストにvertex_vboをGL_ARRAY_BUFFERでバインド。
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), colors.data(), GL_STATIC_DRAW); //実データを格納


	/*

	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	shader->sendVertexAttribute3df("position", positions);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	*/
	glBindVertexArray(vao);

	{
		glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
		auto location = shader->getAttribLocation("position");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	}

	{
		glBindBuffer(GL_ARRAY_BUFFER, size_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
		auto location = shader->getAttribLocation("pointSize");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (GLvoid*)0);
	}


	{
		glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //以下よりcolor_vboでバインドされているバッファが処理される
		auto location = shader->getAttribLocation("color");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	}
//	shader->sendVertexAttribute3df()

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//shader->sendVertexAttribute4df("color", colors);
	//shader->sendVertexAttribute1df("pointSize", sizes);

	/*
	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("color");
	shader->enableVertexAttribute("pointSize");
	*/
}

void PointRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto positions = buffer.getPosition().get();
	//const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto modelviewMatrix = camera.getModelViewMatrix() * Matrix4df(buffer.getMatrix());

	shader->bind();

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);

	/*
	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute4df("color", colors);
	shader->sendVertexAttribute1df("pointSize", sizes);
	*/

	//shader->enableVertexAttribute("position");
	//shader->enableVertexAttribute("color");
	//shader->enableVertexAttribute("pointSize");

	//glDrawArrays()
	glBindVertexArray(vao);
	shader->drawPoints(positions.size() / 3);
	glBindVertexArray(0);

	//shader->disableVertexAttribute("pointSize");
	//shader->disableVertexAttribute("color");
	//shader->disableVertexAttribute("position");

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