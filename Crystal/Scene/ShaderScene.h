#pragma once

#include "IScene.h"

#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class ShaderScene : public IScene
{
public:
	ShaderScene(const int id, const std::string& name, Shader::ShaderObject* shader) :
		IScene(id, name),
		shader(shader)
	{}

	SceneType getType() const override { return SceneType::ShaderScene; }

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

	void onClear() override {
		delete shader;
	}

private:
	Shader::ShaderObject* shader;
};

	}
}