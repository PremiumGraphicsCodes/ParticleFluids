#pragma once

#include "../Shader/ShaderObject.h"

#include "IShader.h"

#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {

class LineShader : public IShader
{
public:
	LineShader();

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void setBuffer(const LineShaderScene& buffer) { this->glBuffer = buffer; }

	void render() override;

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	LineShaderScene glBuffer;
	Shader::ShaderObject shader;
};

	}
}