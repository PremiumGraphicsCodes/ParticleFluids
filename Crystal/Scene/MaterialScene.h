#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"
#include "SceneViewModel.h"

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

	void setMaterial(const Graphics::Material& material) { this->material = material; }

	SceneType getType() const override { return SceneType::MaterialScene; }

	void onClear() override {}

	SceneViewModel toViewModel() const override { return SceneViewModel(); }

private:
	Graphics::Material material;
};

	}
}