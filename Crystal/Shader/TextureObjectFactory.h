#pragma once

#include "../Util/UnCopyable.h"

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

	void clear() { nextId = 0; }

	TextureObject createTextureObject(const Graphics::Image& image);

	TextureObject createTextureObject(const Graphics::Imagef& image);

private:
	int nextId;
};
	}

}