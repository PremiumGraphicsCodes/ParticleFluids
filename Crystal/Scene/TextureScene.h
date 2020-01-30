#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, const Graphics::Image& image, const std::string& name);

	~TextureScene() {};

	void onBuild(Shader::GLObjectFactory& factory) override;

	void onClear() override;

	SceneType getType() const override { return SceneType::TextureScene; }

	void toViewModel(SceneViewModel& viewModel) const override;

	Shader::TextureObject getTextureObject() const { return *texture; }

	void update(const Graphics::Image& image);

private:
	Graphics::Image image;
	Shader::TextureObject* texture;
};

	}
}