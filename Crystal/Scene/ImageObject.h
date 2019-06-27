#pragma once

#include "IScene.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Model {

class ImageObject : public IScene
{
public:
	ImageObject(const int id, const std::string& name, Graphics::Image* image) :
		IScene(id, name),
		image(image)
	{}

	~ImageObject() {};

	Graphics::Image* getImage() const { return image; }

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	bool isNull() const { return image == nullptr; }

	SceneType getType() const override { return SceneType::TextureObject; }

	void onClear() override
	{
		delete image;
	}

private:
	Graphics::Image* image;
};

	}
}