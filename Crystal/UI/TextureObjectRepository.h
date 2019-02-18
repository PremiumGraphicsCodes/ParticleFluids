#pragma once

#include "../Util/UnCopyable.h"
#include "../Shader/TextureObject.h"
#include <vector>

namespace Crystal {
	namespace UI {

class TextureObjectRepository : private UnCopyable
{
public:
	TextureObjectRepository();

	~TextureObjectRepository();

	void clear();

	void add(const Shader::TextureObject& texture, const std::string& name);

	//std::vector<MaterialObject> getMaterials() const { return materials; }

private:
	std::vector<Shader::TextureObject> textures;
	int nextId;
};

	}
}