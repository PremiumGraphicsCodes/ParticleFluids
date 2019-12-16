#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Scene {

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, const Graphics::Material& material, const int materialId) :
		IScene(id, name),
		material(material),
		materialId(materialId)
	{}

	~MaterialScene() {};

	Graphics::Material getMaterial() { return material; }

	void onClear() override {};

	void setMaterial(const Graphics::Material& material) { this->material = material; }

	SceneType getType() const override { return SceneType::MaterialScene; }

	void toViewModel(SceneViewModel& viewModel) const override;
	
	int getMaterialId() const { return materialId; }

private:
	Graphics::Material material;
	int materialId;
};

	}
}