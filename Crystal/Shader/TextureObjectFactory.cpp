#include "TextureObjectFactory.h"

#include "TextureObject.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void TextureObjectFactory::clear()
{
	for (const auto& t : textures) {
		t->clear();
	}
	textures.clear();
	nextId = 0;
}

TextureObject* TextureObjectFactory::createTextureObject(const Image& image)
{
	auto object = std::make_unique<TextureObject>();
	object->create(image, nextId++);
	textures.push_back(std::move( object ));
	return textures.back().get();
}

TextureObject* TextureObjectFactory::createTextureObject(const Imagef& image)
{
	auto object = std::make_unique<TextureObject>();
	object->create(image, nextId++);
	textures.push_back(std::move(object));
	return textures.back().get();
}
