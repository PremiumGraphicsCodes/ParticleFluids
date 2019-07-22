#ifndef __CRYSTAL_SHADER_ON_SCREEN_RENDERER_H__
#define __CRYSTAL_SHADER_ON_SCREEN_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "ITextureObject.h"
#include "ShaderObject.h"
#include "IShader.h"

namespace Crystal {
	namespace Shader {

class OnScreenRenderer
{
public:
	bool build();

	void render(const ITextureObject& texture);

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject* shader;
};

	}
}

#endif