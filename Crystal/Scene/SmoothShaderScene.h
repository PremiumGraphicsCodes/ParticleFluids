#pragma once

#include "SmoothShaderBuffer.h"

#include "../Graphics/Camera.h"
#include "../Graphics/PointLight.h"

#include "../Shader/TextureObject.h"
#include "../Shader/VertexBufferObject.h"
#include "../Shader/ShaderObject.h"

#include "IShader.h"

namespace Crystal {
	namespace Scene {

class SmoothShaderScene : public IShader
{
public:
	SmoothShaderScene();

	bool build() override;

	void release() override;

	void send(const SmoothShaderBuffer& buffer);

	void send(const std::vector<Graphics::Material>& materials);

	void send(const std::vector<Graphics::PointLight>& lights);

	void send(const std::vector<Shader::TextureObject>& texture);

	void render() override;

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Math::Matrix4df matrix;
	int count;
	Shader::ShaderObject shader;
};

	}
}