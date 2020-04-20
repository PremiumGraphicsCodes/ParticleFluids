#pragma once

#include "../Shader/ShaderObject.h"

#include "IShaderScene.h"

#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {
		class CameraShaderScene;

class LineShader : public IShaderScene
{
public:
	explicit LineShader(const std::string& name);

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void setBuffer(LineShaderScene* buffer) { this->glBuffer = buffer; }

	void setCamera(const CameraShaderScene& camera);

	void render() override;

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	LineShaderScene* glBuffer;
	Shader::ShaderObject shader;
};

	}
}