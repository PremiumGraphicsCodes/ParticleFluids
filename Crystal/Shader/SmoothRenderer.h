#ifndef __CRYSTAL_SHADER_SMOOTH_RENDERER_H__
#define __CRYSTAL_SHADER_SMOOTH_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"

#include "ShaderObject.h"
#include "TextureObject.h"

namespace Crystal {
	namespace Shader {

class SmoothRenderer
{
public:
	struct Buffer
	{
		Graphics::TriangleBuffer triangle;
		Graphics::LightBuffer light;
		Graphics::MaterialBuffer material;
	};

	void findLocation();

	void render(const Buffer& buffer, const Graphics::ICamera& camera,const TextureObject& texture);

	bool build();

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

private:
	ShaderObject shader;
};

	}
}

#endif