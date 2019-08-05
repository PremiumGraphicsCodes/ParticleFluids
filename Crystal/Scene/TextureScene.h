#pragma once

#include "IShaderScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IShaderScene
{
public:
	TextureScene(const int id, const std::string& name, const Graphics::Image& image) :
		IShaderScene(id, name),
		image(image),
		texture(nullptr)
	{}

	~TextureScene() {};

	Graphics::Image getImage() const { return image; }

	Shader::TextureObject* getTexture() const { return texture.get(); }

	bool build();

	void render(const Graphics::ICamera& camera) override {}

private:
	Graphics::Image image;
	std::unique_ptr<Shader::TextureObject> texture;
};

	}
}