#pragma once

#include "../Util/UnCopyable.h"
#include "TextureObject.h"
#include <vector>

namespace Crystal {
	namespace Shader {

class TextureObjectRepository : private UnCopyable
{
public:
	TextureObjectRepository();

	~TextureObjectRepository();

	void clear();

	void add(const Graphics::Image& image, const std::string& name);

	TextureObject* findObjectById(const int id) const;

	std::vector<TextureObject*> getTextures() const { return textures; }

private:
	std::vector<TextureObject*> textures;
	int nextId;
};

	}
}