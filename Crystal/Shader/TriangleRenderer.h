#pragma once

#include "../Graphics/ICamera.h"
#include "../Graphics/TriangleBuffer.h"
#include "IShader.h"

#include "ShaderObject.h"

namespace Crystal {
	namespace Shader {

class TriangleRenderer : public IShader
{
public:
	void findLocation();

	void setBuffer(const Graphics::TriangleBuffer& buffer) { this->buffer = buffer; }

	void render(const Graphics::ICamera& camera) override;

	bool build() override;

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

private:
	ShaderObject shader;
	Graphics::TriangleBuffer buffer;
};

	}
}
