#pragma once

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"

#include "PointShaderBuffer.h"

namespace Crystal {
	namespace Scene {

class PointShaderScene
{
public:
	PointShaderScene();

	bool build();

	void send(const PointShaderBuffer& buffer, const Graphics::Camera& camera);

	void render();

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject shader;

	int count;
};

	}
}