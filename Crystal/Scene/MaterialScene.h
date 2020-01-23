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
		material(material),
		ambientTexture(nullptr),
		diffuseTexture(nullptr),
		specularTexture(nullptr)
	{}

	~MaterialScene() {};

	Graphics::Material getMaterial() { return material; }

	void setMaterial(const Graphics::Material& material);

	void setAmbientTexture(TextureScene* texture) { this->ambientTexture = texture; }

	void setDiffuseTexture(TextureScene* texture) { this->diffuseTexture = texture; }

	void setSpecularTexture(TextureScene* texture) { this->specularTexture = texture; }

	TextureScene* getAmbientTexture() const;

	TextureScene* getDiffuseTexture() const;

	TextureScene* getSpecularTexture() const;

	void onClear() override {};

	SceneType getType() const override { return SceneType::MaterialScene; }

	void toViewModel(SceneViewModel& viewModel) const override;
	
	int getMaterialId() const { return materialId; }

private:
	Graphics::Material material;
	TextureScene* ambientTexture;
	TextureScene* diffuseTexture;
	TextureScene* specularTexture;
	int materialId;
};

	}
}