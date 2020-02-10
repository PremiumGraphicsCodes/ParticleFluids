#include "TextureObjectFactory.h"

#include "TextureObject.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void TextureObjectFactory::clear()
{
	nextId = 0;
}

TextureObject TextureObjectFactory::createTextureObject(const std::string& name, const Image& image)
{
	auto object = TextureObject();
	object.create(image, nextId++);
	return object;
}

TextureObject TextureObjectFactory::createTextureObject(const std::string& name, const Imagef& image)
{
	auto object = TextureObject();
	object.create(image, nextId++);
	return object;
}
