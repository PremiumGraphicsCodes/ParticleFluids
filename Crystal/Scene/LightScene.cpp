#include "LightScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

LightScene::LightScene(const int id, const std::string& name, std::unique_ptr<PointLight> light) :
	IScene(id, name),
	light(std::move(light))
{}

void LightScene::send(SceneViewModel& viewModel)
{
	viewModel.lights.push_back(*light);
}