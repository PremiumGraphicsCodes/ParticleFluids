#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, const std::string& name, const Graphics::Image& image);

	~TextureScene() {};

	Graphics::Image getImage() { return image; }

	void onClear() override;

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	SceneType getType() const override { return SceneType::TextureScene; }

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& viewModel) const override;

	bool build();

private:
	Graphics::Image image;
	Shader::TextureObject texture;
};

	}
}