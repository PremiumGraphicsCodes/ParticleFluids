#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, const std::string& name, const Graphics::Image& image) :
		IScene(id, name),
		image(image),
		texture(nullptr)
	{}

	~TextureScene() {};

	Graphics::Image getImage() const { return image; }

	Shader::TextureObject* getTexture() const { return texture.get(); }

	SceneType getType() const override { return SceneType::TextureScene; }

	void onClear() override { texture.reset(); }

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

	bool build();

private:
	Graphics::Image image;
	std::unique_ptr<Shader::TextureObject> texture;
};

	}
}