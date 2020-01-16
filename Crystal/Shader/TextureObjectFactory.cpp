#include "TextureObjectFactory.h"

#include "TextureObject.h"

#include "../Graphics/Image.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TextureObject TextureObjectFactory::createTextureObject(const Image& image)
{
	TextureObject object;
	object.create(image, nextId++);
	return object;
}

TextureObject TextureObjectFactory::createTextureObject(const Imagef& image)
{
	TextureObject object;
	object.create(image, nextId++);
	return object;
}
