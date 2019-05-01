#pragma once

#include "../Util/UnCopyable.h"
#include "TextureObjectRepository.h"
#include "ShaderObjectRepository.h"

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

	ShaderObjectRepository* getShaders() { return &shaders; }

private:
	TextureObjectRepository textures;
	ShaderObjectRepository shaders;
};

	}
}