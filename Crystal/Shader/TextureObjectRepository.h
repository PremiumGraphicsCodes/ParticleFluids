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

	int add(const Graphics::Image& image, const std::string& name);

	TextureObject* findObjectById(const int id) const;

	std::vector<TextureObject*> getTextures() const { return textures; }

	void setOnScreenTexture(TextureObject* texture) { this->onScreenTexture = texture; }

	TextureObject* getOnScreenTexture() const { return onScreenTexture; }

private:
	std::vector<TextureObject*> textures;
	TextureObject* onScreenTexture;
	int nextId;
};

	}
}