#pragma once

#include "../Graphics/ICamera.h"
#include "../Graphics/LineBuffer.h"
#include "IShader.h"

#include "ShaderObject.h"

namespace Crystal {
	namespace Shader {

class LineRenderer : public IShader
{
public:
	void findLocation();

	void setBuffer(const Graphics::LineBuffer& buffer, const float width) {
		this->buffer = buffer;
		this->width = width;
	}

	void render(const Graphics::ICamera& camera) override;

	bool build() override;

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

private:
	ShaderObject shader;
	Graphics::LineBuffer buffer;
	float width;
};

	}
}
