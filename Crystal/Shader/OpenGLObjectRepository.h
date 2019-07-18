#pragma once

#include "../Util/UnCopyable.h"
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

	ShaderObjectRepository* getShaders() { return &shaders; }

private:
	ShaderObjectRepository shaders;
};

	}
}