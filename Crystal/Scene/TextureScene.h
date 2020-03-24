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

	SceneType getType() const override { return SceneType::TextureScene; }

	Shader::TextureObject getTextureObject() const { return texture; }

	void setImage(std::unique_ptr<Graphics::Image> image) { this->image = std::move(image); }

private:
	std::unique_ptr<Graphics::Image> image;
	Shader::TextureObject texture;
};

	}
}