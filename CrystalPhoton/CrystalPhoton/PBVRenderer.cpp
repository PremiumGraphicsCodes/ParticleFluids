#include "PBVRenderer.h"

//#include "CameraShaderScene.h"
#include "Crystal/Shader/ShaderObject.h"

#include <sstream>

using namespace Crystal::Math;
//using namespace Crystal::Graphics;
using namespace Crystal::Shader;
//using namespace Crystal::Scene;
using namespace Crystal::Photon;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto colorLabel = "color";
	constexpr auto sizeLabel = "pointSize";
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto fragColorLabel = "fragColor";
}

PBVRenderer::PBVRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus PBVRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	status.isOk = true;

	const auto& vsSource = getBuiltInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	status.log = shader->getLog();
	if (!isOk) {
		status.isOk = false;
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);
	shader->findAttribLocation(::sizeLabel);

	return status;
}

void PBVRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void PBVRenderer::render(const Buffer& buffer)
{
	shader->bind();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute4df(::colorLabel, buffer.color);
	shader->sendVertexAttribute1df(::sizeLabel, buffer.size);

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->drawPoints(buffer.count);

	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();
	shader->disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}

std::string PBVRenderer::getBuiltInVertexShaderSource() const
{
	// noise function is from https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "float rand(float n){return fract(sin(n) * 43758.5453123);}" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float n1 = rand(position.x) * 0.1;" << std::endl
		<< "	float n2 = rand(position.y) * 0.1;" << std::endl
		<< "	float n3 = rand(position.z) * 0.1;" << std::endl
		<< "	vec3 v = vec3(n1,n2,n3);" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position + v, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vColor = color;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string PBVRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "float rand(vec2 co){" << std::endl
		<< "	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453); }" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec2 coord = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = 1.0 - dot(coord, coord);" << std::endl
		<< "	if (distSquared < 0.0) {" << std::endl
		<< "		discard;" << std::endl
		<< "	}" << std::endl
		<< "	fragColor.rgba = vColor;" << std::endl
//		<< "	float random = rand(gl_FragCoord.xy);" << std::endl
//		<< "	fragColor.r = random;"<< std::endl
//		<< "	fragColor.g = random;" << std::endl
//		<< "	fragColor.b = random;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}