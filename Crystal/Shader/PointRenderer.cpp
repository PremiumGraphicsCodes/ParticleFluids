#include "PointRenderer.h"

//#include "CameraShaderScene.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
//using namespace Crystal::Scene;


namespace {
	constexpr char* positionLabel = "position";
	constexpr char* colorLabel = "color";
	constexpr char* sizeLabel = "pointSize";
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr char* fragColorLabel = "fragColor";
}

bool PointRenderer::build(GLObjectFactory& factory)
{
	const auto& vsSource = getBuiltInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	const auto isOk = shader.build(vsSource, fsSource);

	shader.findUniformLocation(::projectionMatrixLabel);
	shader.findUniformLocation(::modelViewMatrixLabel);

	shader.findAttribLocation(::positionLabel);
	shader.findAttribLocation(::colorLabel);
	shader.findAttribLocation(::sizeLabel);

	return isOk;
}

void PointRenderer::release(GLObjectFactory& factory)
{
	shader.release();
}

void PointRenderer::send(const Buffer& buffer)
{
	shader.bind();

	shader.sendVertexAttribute3df(::positionLabel, buffer.position);
	shader.sendVertexAttribute4df(::colorLabel, buffer.color);
	shader.sendVertexAttribute1df(::sizeLabel, buffer.size);

	shader.unbind();
}

void PointRenderer::render(const Graphics::Camera& camera, const int count)
{
	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix();

	shader.sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader.sendUniform(::modelViewMatrixLabel, modelviewMatrix);


	shader.bind();

	shader.enableDepthTest();
	shader.enablePointSprite();

	shader.drawPoints(count);

	shader.bindOutput(::fragColorLabel);

	shader.disablePointSprite();
	shader.disableDepthTest();

	shader.unbind();

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