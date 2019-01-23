#ifndef __CRYSTAL_SHADER_SMOOTH_RENDERER_H__
#define __CRYSTAL_SHADER_SMOOTH_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/LightBuffer.h"

#include "ShaderObject.h"
#include "TextureObject.h"

namespace Crystal {
	namespace Shader {

class SmoothRenderer
{
public:
	void findLocation();

	void setBuffer(const Graphics::TriangleBuffer& buffer, const Graphics::LightBuffer& light) {
		this->buffer = buffer;
		this->light = light;
	}

	void render(const Graphics::ICamera& camera,const TextureObject& texture);

	bool build();

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

private:
	ShaderObject shader;
	Graphics::TriangleBuffer buffer;
	Graphics::LightBuffer light;
};

	}
}

#endif