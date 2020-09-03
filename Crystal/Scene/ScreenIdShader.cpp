#include "ScreenIdShader.h"

#include "../Shader/GLObjectFactory.h"

#include "PointShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenIdShader::ScreenIdShader(const std::string& name)
{
	texture = new TextureShaderScene("IdTexture");
}

bool ScreenIdShader::build(GLObjectFactory& factory)
{
	frameBufferObject = factory.getFrameBufferFactory()->create(512, 512);

	texture->build(factory);
	texture->send(Image(512, 512));
	//texture = factory.getTextureFactory()->createTextureObject("SceneId", Imagef(512, 512));

	return true;
}

void ScreenIdShader::release(GLObjectFactory& factory)
{

}

void ScreenIdShader::render(std::vector<IShaderScene*> scenes, const Graphics::Camera& camera)
{
	frameBufferObject->setTexture(*texture->getTextureObject());
	//texture.bind();
	frameBufferObject->bind();
	glViewport(0, 0, texture->getTextureObject()->getWidth(), texture->getTextureObject()->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto s : scenes) {
		s->render(camera);
	}

	frameBufferObject->unbind();
}

DrawableID ScreenIdShader::getId(const double x, const double y)
{
	return getIdInTexCoord(x * texture->getTextureObject()->getWidth(), y * texture->getTextureObject()->getHeight());
}

DrawableID ScreenIdShader::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject->bind();
	glViewport(0, 0, texture->getTextureObject()->getWidth(), texture->getTextureObject()->getHeight());
	const auto& color = frameBufferObject->getColor(x, y);
	frameBufferObject->unbind();
	return DrawableID(color);
}