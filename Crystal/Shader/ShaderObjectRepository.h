#pragma once

#include "../Util/UnCopyable.h"
#include "ShaderObject.h"

namespace Crystal {
	namespace Shader {

class ShaderObjectRepository : private UnCopyable
{
public:

private:
	std::vector<ShaderObject*> shaders;
};
	}
}