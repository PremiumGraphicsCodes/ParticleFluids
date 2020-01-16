#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, const Shader::TextureObject& texture, const std::string& name);

	~TextureScene() {};

	void onClear() override;

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	SceneType getType() const override { return SceneType::TextureScene; }

	void toViewModel(SceneViewModel& viewModel) const override;

private:
	Shader::TextureObject texture;
};

	}
}