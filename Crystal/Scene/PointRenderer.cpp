#include "PointRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr char* positionLabel = "position";
	constexpr char* colorLabel = "color";
	constexpr char* sizeLabel = "pointSize";
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr char* fragColorLabel = "fragColor";
}

void PointRenderer::GLBuffer::build()
{
	vbo.position.build();
	vbo.size.build();
	vbo.color.build();

	//vao.build();
}

void PointRenderer::GLBuffer::release()
{
	vbo.position.release();
	vbo.size.release();
	vbo.color.release();

	//vao.release();
}


void PointRenderer::GLBuffer::send(const PointBuffer& buffer)
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


PointRenderer::PointRenderer()
{
}

bool PointRenderer::build(GLObjectFactory& factory)
{
	setVertexShaderSource(getBuiltInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform(::projectionMatrixLabel);
	addUniform(::modelViewMatrixLabel);

	addAttribute(::positionLabel);
	addAttribute(::colorLabel);
	addAttribute(::sizeLabel);


	return build_(factory);
}


void PointRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto modelviewMatrix = camera.getModelViewMatrix() * glBuffer.matrix;

	shader->bind();

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, modelviewMatrix);

	//glBuffer.vao.bind();
	shader->sendVertexAttribute3df(::positionLabel, glBuffer.vbo.position);
	shader->sendVertexAttribute4df(::colorLabel, glBuffer.vbo.color);
	shader->sendVertexAttribute1df(::sizeLabel, glBuffer.vbo.size);

	shader->drawPoints(glBuffer.count);
	//glBuffer.vao.unbind();

	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();
	shader->disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());

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