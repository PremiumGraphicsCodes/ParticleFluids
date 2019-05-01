#pragma once

#include "../Util/UnCopyable.h"
#include "TextureObjectRepository.h"

namespace Crystal {
	namespace Shader {

class OpenGLObjectRepository : private UnCopyable
{
public:
	OpenGLObjectRepository()
	{}

	~OpenGLObjectRepository()
	{}

	void clear();

	TextureObjectRepository* getTextures() { return &textures; }

private:
	TextureObjectRepository textures;
};

	}
}