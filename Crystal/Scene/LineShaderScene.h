#pragma once

#include "../Shader/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

#include "LineShaderBuffer.h"

namespace Crystal {
	namespace Scene {

class LineShaderScene
{
public:
	LineShaderScene();

	bool build();

	void setBuffer(const LineShaderBuffer& buffer) { this->glBuffer = buffer; }

	void render(const Graphics::Camera& camera);

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	LineShaderBuffer glBuffer;
	Shader::ShaderObject shader;
};

	}
}