#pragma once

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"

#include "PointShaderScene.h"
#include "IShader.h"

namespace Crystal {
	namespace Scene {
		class CameraShaderScene;

class PointShader : public IShader
{
public:
	PointShader();

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void send(const PointShaderScene& buffer);

	void send(const CameraShaderScene& camera);

	void render() override;

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject shader;

	int count;
};

	}
}