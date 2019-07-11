#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Scene {

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, Graphics::Material* material) :
		IScene(id, name),
		material(material)
	{}

	~MaterialScene() {};

	Graphics::Material* getMaterial() { return material; }

	void setMaterial(const Graphics::Material& material) { *this->material = material; }

	bool isNull() const { return material == nullptr; }

	SceneType getType() const override { return SceneType::MaterialScene; }

	void onClear() override
	{
		delete material;
	}


private:
	Graphics::Material* material;
};

	}
}