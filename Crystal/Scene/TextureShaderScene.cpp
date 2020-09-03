#include "TextureShaderScene.h"

#include "../Shader/GLObjectFactory.h"
#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureShaderScene::TextureShaderScene(const std::string& name) :
	IShaderScene(name)
{}

bool TextureShaderScene::build(GLObjectFactory& factory)
{
	this->textureObject = factory.getTextureFactory()->createTextureObject(getName());
	return true;
}

void TextureShaderScene::release(GLObjectFactory& glFactory)
{
	this->textureObject.clear();
}

void TextureShaderScene::render(const Camera& camera)
{

}

void TextureShaderScene::send(const Image& image)
{
	this->textureObject.send(image);
}