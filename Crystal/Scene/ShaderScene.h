#pragma once

#include "IScene.h"

#include "../Shader/ShaderObject.h"

#include <memory>

namespace Crystal {
	namespace Scene {

class ShaderScene : public IScene
{
public:
	ShaderScene(const int id, const std::string& name, const std::string& vsSource, const std::string& fsSource) :
		IScene(id, name),
		vsSource(vsSource),
		fsSource(fsSource)
	{}

	void addUniform(const std::string& name) { uniforms.push_back(name); }

	void addAttribute(const std::string& name) { attributes.push_back(name); }

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