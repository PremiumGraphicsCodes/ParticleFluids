#pragma once

#include "ShaderScene.h"

#include "../Shader/ShaderObject.h"

#include "../Graphics/LineBuffer.h"
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Scene {

class LineShaderScene : public ShaderScene
{
public:
	LineShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	Graphics::LineBuffer buffer;
	float width;
	Shader::ShaderObject* shader;
};

	}
}