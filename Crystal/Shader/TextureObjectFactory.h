#pragma once

#include "../Util/UnCopyable.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Graphics {
		class Image;
		class Imagef;
	}
	namespace Shader {

class TextureObject;

class TextureObjectFactory : private UnCopyable
{
public:
	TextureObjectFactory() :
		nextId(0)
	{}

	void clear();

	std::unique_ptr<TextureObject> createTextureObject(const Graphics::Image& image);

	std::unique_ptr<TextureObject> createTextureObject(const Graphics::Imagef& image);

private:
	int nextId;
};
	}

}