#pragma once

#include "ShaderScene.h"

#include "../Shader/ShaderObject.h"

#include "../Graphics/PointBuffer.h"
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Scene {

class PointShaderScene : public ShaderScene
{
public:
	PointShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const Graphics::PointBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	Graphics::PointBuffer buffer;
};

	}
}