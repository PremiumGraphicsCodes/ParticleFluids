#include "GLObjectFactory.h"

#include "TextureObject.h"
#include "FrameBufferObject.h"
#include "VertexBufferObject.h"
#include "ShaderObject.h"

using namespace Crystal::Shader;

void GLObjectFactory::clear()
{
	textures.clear();
	shaders.clear();
	vbos.clear();
	fbos.clear();
}

FrameBufferObject* GLObjectFactory::createFrameBufferObject()
{
	auto fbo = std::make_unique<FrameBufferObject>();
	fbos.push_back(std::move(fbo));
	return fbos.back().get();
}

VertexBufferObject* GLObjectFactory::createVertexBufferObject()
{
	auto vbo = std::make_unique<VertexBufferObject>();
	vbos.push_back(std::move(vbo));
	return vbos.back().get();
}

ShaderObject* GLObjectFactory::createShaderObject()
{
	auto shader = std::make_unique<ShaderObject>();
	shaders.push_back(std::move(shader));
	return shaders.back().get();
}

TextureObject* GLObjectFactory::createTextureObject()
{
	auto texture = std::make_unique<TextureObject>();
	texture->create("");
	textures.push_back(std::move(texture));
	return textures.back().get();
}
