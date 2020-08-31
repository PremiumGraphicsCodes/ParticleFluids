#include "TextureObjectFactory.h"

#include "TextureObject.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void TextureObjectFactory::clear()
{
}

TextureObject TextureObjectFactory::createTextureObject(const std::string& name)
{
	auto object = TextureObject();
	object.create(name);
	return object;
}

TextureObject TextureObjectFactory::createTextureObject(const std::string& name, const Image& image)
{
	auto object = TextureObject();
	object.create(name);
	object.bind(0);
	object.send(image);
	object.unbind();
	return object;
}

TextureObject TextureObjectFactory::createTextureObject(const std::string& name, const Imagef& image)
{
	auto object = TextureObject();
	object.create(name);
	object.bind(0);
	object.send(image);
	object.unbind();
	return object;
}
