#pragma once

#include "../Util/UnCopyable.h"

#include <string>
#include <list>
#include <memory>
#include <map>

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
	TextureObjectFactory()
	{}

	void clear();

	TextureObject createTextureObject(const std::string& name);

	TextureObject createTextureObject(const std::string& name, const Graphics::Image& image);

	TextureObject createTextureObject(const std::string& name, const Graphics::Imagef& image);

private:
	//std::map<std::string, TextureObject> textures;
};
	}

}