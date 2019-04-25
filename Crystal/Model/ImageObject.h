#pragma once

#include "IObject.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Model {

class ImageObject : public IObject
{
public:
	ImageObject(const int id, const std::string& name, Graphics::Image* image) :
		IObject(id, name),
		image(image)
	{}

	~ImageObject() {};

	Graphics::Image* getImage() const { return image; }

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	void move(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) { ; }

	void transform(const Math::Matrix4dd& m) { ; }

	bool isNull() const { return image == nullptr; }

	ObjectType getType() const override { return ObjectType::TextureObject; }

private:
	Graphics::Image* image;
};

	}
}