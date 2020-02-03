#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, std::unique_ptr<Graphics::Image> image, const std::string& name);

	~TextureScene() {};

	void onBuild(Shader::GLObjectFactory& factory) override;

	void onClear() override;

	SceneType getType() const override { return SceneType::TextureScene; }

	void toViewModel(SceneViewModel& viewModel) const override;

	Shader::TextureObject getTextureObject() const { return *texture; }

	void onSend() override;

	void setImage(std::unique_ptr<Graphics::Image> image) { this->image = std::move(image); }

private:
	std::unique_ptr<Graphics::Image> image;
	std::unique_ptr<Shader::TextureObject> texture;
};

	}
}