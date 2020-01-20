#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, const Graphics::Material& material, const int materialId) :
		IScene(id, name),
		material(material)
	{}

	~MaterialScene() {};

	Graphics::Material getMaterial() { return material; }

	void setMaterial(const Graphics::Material& material);

	TextureScene* getAmbientTexture() const;

	void onClear() override {};

	SceneType getType() const override { return SceneType::MaterialScene; }

	void toViewModel(SceneViewModel& viewModel) const override;
	
	int getMaterialId() const { return materialId; }

private:
	Graphics::Material material;
	TextureScene* ambientTexture;
	int materialId;
};

	}
}