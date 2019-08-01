#pragma once

#include "IScene.h"

#include "../Shader/ShaderObject.h"

#include <memory>

namespace Crystal {
	namespace Scene {

class ShaderScene : public IScene
{
public:
	ShaderScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	void setVertexShaderSource(const std::string& vsSource) { this->vsSource = vsSource; }

	void setFragmentShaderSource(const std::string& fsSource) { this->fsSource = fsSource; }

	void addUniform(const std::string& name) { uniforms.push_back(name); }

	void addAttribute(const std::string& name) { attributes.push_back(name); }

	std::string getVertexShaderSource() const { return vsSource; }

	std::string getFragmentShaderSource() const { return fsSource; }

	SceneType getType() const override { return SceneType::ShaderScene; }

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

	void onClear() override { shader.reset(); }

	Shader::ShaderObject* getShader() { return shader.get(); }

	bool build() override;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
	std::string vsSource;
	std::string fsSource;
	std::vector<std::string> uniforms;
	std::vector<std::string> attributes;
};

	}
}