#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Scene {

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, const Graphics::Material& material) :
		IScene(id, name),
		material(material)
	{}

	~MaterialScene() {};

	Graphics::Material getMaterial() { return material; }

	void onClear() override {};

	void setMaterial(const Graphics::Material& material) { this->material = material; }

	SceneType getType() const override { return SceneType::MaterialScene; }

	SceneViewModel toViewModel() const override;

	SceneIdViewModel toIdViewModel() const override;

private:
	Graphics::Material material;
};

	}
}