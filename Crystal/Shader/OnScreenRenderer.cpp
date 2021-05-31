#include "OnScreenRenderer.h"

#include "../Math/Vector2d.h"
#include "../Math/Box2d.h"

#include "GLObjectFactory.h"
#include "TextureObject.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ShaderBuildStatus OnScreenRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	this->shader = factory.createShaderObject();
	if(!this->shader->build(vsSource, fsSource)){
		status.isOk = false;
		status.log += this->shader->getLog();
		return status;
	}
	findLocation();
	return status;
}

void OnScreenRenderer::release(GLObjectFactory& factory)
{
	factory.remove(this->shader);
}

std::string OnScreenRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec2 position;" << std::endl
		<< "out vec2 texCoord;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	texCoord = (position + vec2(1.0,1.0))/2.0;" << std::endl
		<< "	gl_Position = vec4(position, 0.0, 1.0);" << std::endl
		<< "}" << std::endl;
	ShaderUnit vertexShader;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string OnScreenRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D texture;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = texture2D(texture, texCoord);" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void OnScreenRenderer::findLocation()
{
	shader->findUniformLocation("texture");
	shader->findAttribLocation("position");
}

void OnScreenRenderer::render(const ITextureObject& texture)
{
	const Box2d box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto& positions = box.toArray();

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->getHandle());

	texture.bind(0);

	glUniform1i(shader->getUniformLocation("texture"), 0);

	glVertexAttribPointer(shader->getAttribLocation("position"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getHandle(), 0, "fragColor");

	texture.unbind();
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}