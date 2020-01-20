#pragma once

#include "../Util/UnCopyable.h"
#include "ShaderObject.h"

#include <list>

namespace Crystal {
	namespace Shader {

class ShaderObjectFactory : private UnCopyable
{
public:
	void clear();

	ShaderObject* create(const std::string& vsSource, const std::string& fsSource);

	//FrameBufferObject create();

	//FrameBufferObject create(const Graphics::Imagef& image);

private:
	std::list<std::unique_ptr<ShaderObject>> shaders;
	//int nextId;

};

	}
}