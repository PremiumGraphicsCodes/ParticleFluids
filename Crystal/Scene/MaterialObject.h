#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Model {

class MaterialObject : public IScene
{
public:
	MaterialObject(const int id, const std::string& name, Graphics::Material* material) :
		IScene(id, name),
		material(material)
	{}

	~MaterialObject() {};

	Graphics::Material* getMaterial() const { return material; }

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	void move(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) { ; }

	void transform(const Math::Matrix4dd& m) { ; }

	bool isNull() const { return material == nullptr; }

	ObjectType getType() const override { return ObjectType::MaterialObject; }

private:
	Graphics::Material* material;
};

	}
}