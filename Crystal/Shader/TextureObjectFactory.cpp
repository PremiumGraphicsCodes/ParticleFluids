#include "TextureObjectFactory.h"

#include "TextureObject.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void TextureObjectFactory::clear()
{
	nextId = 0;
}

std::unique_ptr<TextureObject> TextureObjectFactory::createTextureObject(const Image& image)
{
	auto object = std::make_unique<TextureObject>();
	object->create(image, nextId++);
	return std::move( object );
}

std::unique_ptr<TextureObject> TextureObjectFactory::createTextureObject(const Imagef& image)
{
	auto object = std::make_unique<TextureObject>();
	object->create(image, nextId++);
	return std::move(object);
}
