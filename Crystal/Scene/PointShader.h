#pragma once

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"

#include "PointShaderBuffer.h"
#include "IShader.h"

namespace Crystal {
	namespace Scene {

class PointShader : public IShader
{
public:
	PointShader();

	bool build(Shader::GLObjectFactory& factory) override;

	void release() override;

	void send(const PointShaderBuffer& buffer);

	void render() override;

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject shader;

	int count;
};

	}
}