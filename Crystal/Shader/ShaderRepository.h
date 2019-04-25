#pragma once

#include "../Util/UnCopyable.h"
#include "TextureObjectRepository.h"

namespace Crystal {
	namespace Shader {

class ShaderObjectRepository : private UnCopyable
{
public:
	ShaderObjectRepository()
	{}

	~ShaderObjectRepository()
	{}

	void clear();

	TextureObjectRepository* getTextures() { return &textures; }

private:
	TextureObjectRepository textures;
};

	}
}