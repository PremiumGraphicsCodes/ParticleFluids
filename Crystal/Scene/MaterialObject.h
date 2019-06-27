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

	bool isNull() const { return material == nullptr; }

	SceneType getType() const override { return SceneType::MaterialObject; }

private:
	Graphics::Material* material;
};

	}
}