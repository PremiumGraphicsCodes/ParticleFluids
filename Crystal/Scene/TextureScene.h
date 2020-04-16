#pragma once

#include "IScene.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, std::unique_ptr<Graphics::Image> image, const std::string& name);

	~TextureScene() {};

	SceneType getType() const override { return SceneType::TextureScene; }

	void setImage(std::unique_ptr<Graphics::Image> image) { this->image = std::move(image); }

	Graphics::Image* getImage() { return image.get(); }

private:
	std::unique_ptr<Graphics::Image> image;
};

	}
}