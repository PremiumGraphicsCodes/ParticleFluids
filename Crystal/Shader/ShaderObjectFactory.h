#pragma once

#include "../Util/UnCopyable.h"
#include "ShaderObject.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Shader {

class ShaderObjectFactory : private UnCopyable
{
public:
	void clear();

	std::unique_ptr<ShaderObject> create(const std::string& vsSource, const std::string& fsSource);

private:
	std::vector<std::unique_ptr<ShaderObject>> shaders;
	//int nextId;

};

	}
}