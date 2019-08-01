#pragma once

#include "ShaderScene.h"

#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class PointShaderScene : public ShaderScene
{
public:
	PointShaderScene(const int id, const std::string& name, Shader::ShaderObject* shader) :
		ShaderScene(id, name, shader)
	{}

	SceneType getType() const override { return SceneType::ShaderScene; }

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

	void onClear() override {
		delete shader;
	}

private:
};

	}
}