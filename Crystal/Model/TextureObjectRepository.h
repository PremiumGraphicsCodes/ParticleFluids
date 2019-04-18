#pragma once

#include "../Util/UnCopyable.h"
#include "../Shader/TextureObject.h"
#include <vector>

namespace Crystal {
	namespace Model {

class TextureObjectRepository : private UnCopyable
{
public:
	TextureObjectRepository();

	~TextureObjectRepository();

	void clear();

	void add(const Graphics::Image& image, const std::string& name);

	Shader::TextureObject* findObjectById(const int id) const;

	std::vector<Shader::TextureObject*> getTextures() const { return textures; }

private:
	std::vector<Shader::TextureObject*> textures;
	int nextId;
};

	}
}