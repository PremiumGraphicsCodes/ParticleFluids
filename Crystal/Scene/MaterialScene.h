#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"
#include <memory>

namespace Crystal {
	namespace Scene {
		class TextureScene;

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, std::unique_ptr<Graphics::Material> material, const int materialId);

	~MaterialScene() {};

	Graphics::Material* getMaterial() { return material.get(); }

	TextureScene* getAmbientTexture() const;

	TextureScene* getDiffuseTexture() const;

	TextureScene* getSpecularTexture() const;

	void setAmbientTexture(TextureScene* texture);

	void setDiffuseTexture(TextureScene* texture);

	void setSpecularTexture(TextureScene* texture);

	void onClear() override {};

	SceneType getType() const override { return SceneType::MaterialScene; }

	void toViewModel(SceneViewModel& viewModel) const override;
	
	int getMaterialId() const { return materialId; }

private:
	std::unique_ptr<Graphics::Material> material;
	TextureScene* ambientTexture;
	TextureScene* diffuseTexture;
	TextureScene* specularTexture;
	const int materialId;
};

	}
}