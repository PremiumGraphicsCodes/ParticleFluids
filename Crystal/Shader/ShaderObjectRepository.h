#pragma once

#include "../Util/UnCopyable.h"
#include "ShaderObject.h"

namespace Crystal {
	namespace Shader {

class ShaderObjectRepository : private UnCopyable
{
public:
	ShaderObjectRepository();

	~ShaderObjectRepository();

	void clear();

	int add(const std::string& vsSource, const std::string& fsSource);

	ShaderObject* findObjectById(const int id) const;

private:
	std::vector<ShaderObject*> shaders;
};
	}
}