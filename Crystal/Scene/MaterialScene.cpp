#include "MaterialScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "TextureScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

MaterialScene::MaterialScene(const int id, const std::string& name, std::unique_ptr<Material> material, const int materialId) :
	IScene(id, name),
	material(std::move(material)),
	ambientTexture(nullptr),
	diffuseTexture(nullptr),
	specularTexture(nullptr),
	materialId(materialId)
{}

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

void MaterialScene::setAmbientTexture(TextureScene* texture)
{
	this->ambientTexture = texture;
}

void MaterialScene::setDiffuseTexture(TextureScene* texture)
{
	this->diffuseTexture = texture;
}

void MaterialScene::setSpecularTexture(TextureScene* texture)
{
	this->specularTexture = texture;
}

void MaterialScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.materials.push_back(*material);
}
