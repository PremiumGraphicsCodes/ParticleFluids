#include "TextureShaderScene.h"

#include "../Shader/GLObjectFactory.h"
#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool TextureShaderScene::build(GLObjectFactory& factory)
{
	//factory.getTextureFactory()->createTextureObject("SmoothTex01", Imagef(512, 512));
	return true;
}

void TextureShaderScene::release(GLObjectFactory& glFactory)
{

}

void TextureShaderScene::render()
{

}

void TextureShaderScene::send(const Image& image)
{

}

/*
bool TextureShaderBuffer::build(GLObjectFactory& factory)
{
	for (int i = 0; i < 8; ++i) {
		factory.getTextureFactory()->createTextureObject("SmoothTex01", Imagef(512, 512));
	}
	return false;
}
*/
