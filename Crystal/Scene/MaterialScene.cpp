#include "MaterialScene.h"
#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "TextureScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

MaterialScene::MaterialScene(const int id, const std::string& name, std::unique_ptr<Material> material, const int materialId) :
	IScene(id, name),
	material(std::move(material)),
	materialId(materialId)
{}

void MaterialScene::send(SceneViewModel& viewModel)
{
	viewModel.materials.push_back(*material);
}
