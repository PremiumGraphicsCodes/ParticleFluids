#include "TextureScene.h"
#include "../Scene/ViewModel.h"
#include "../Scene/SceneIdViewModel.h"

using namespace Crystal::Scene;

SceneViewModel TextureScene::toViewModel() const
{
	return SceneViewModel();
}

SceneIdViewModel TextureScene::toIdViewModel() const
{
	return SceneIdViewModel();
}

bool TextureScene::build()
{
	this->texture = std::make_unique<Crystal::Shader::TextureObject>();
	this->texture->create(image);
	return true;
}