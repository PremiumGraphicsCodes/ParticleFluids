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
}

TextureScene* MaterialScene::getAmbientTexture() const
{
	return ambientTexture;
}

void MaterialScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.materials.push_back(material);
}
