#pragma once

#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Shader {
		class ShaderObjectRepository;

class IShader
{
public:
	virtual ~IShader() {}

	virtual bool build(ShaderObjectRepository& shaders) = 0;

	virtual void render(const Graphics::ICamera& camera) = 0;

	//virtual ShaderObject* getShader() = 0;
};

	}
}
