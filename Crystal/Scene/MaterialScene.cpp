#include "MaterialScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "TextureScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void MaterialScene::setMaterial(const Material& material)
{
	this->material = material;

	if (!material.ambientTextureName.empty()) {
		auto scene = getRoot()->findSceneByName<TextureScene*>(material.ambientTextureName);
		this->ambientTexture = scene;
	}

	if (!material.diffuseTextureName.empty()) {
		auto scene = getRoot()->findSceneByName<TextureScene*>(material.diffuseTextureName);
		this->diffuseTexture = scene;
	}

	if (!material.specularTextureName.empty()) {
		auto scene = getRoot()->findSceneByName<TextureScene*>(material.specularTextureName);
		this->specularTexture = scene;
	}
}

TextureScene* MaterialScene::getAmbientTexture() const
{
	return ambientTexture;
}

TextureScene* MaterialScene::getDiffuseTexture() const
{
	return diffuseTexture;
}

TextureScene* MaterialScene::getSpecularTexture() const
{
	return specularTexture;
}

void MaterialScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.materials.push_back(material);
}
