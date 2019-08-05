#include "TextureScene.h"
#include "../Scene/ViewModel.h"
#include "../Scene/SceneIdViewModel.h"

using namespace Crystal::Scene;

bool TextureScene::build()
{
	this->texture = std::make_unique<Crystal::Shader::TextureObject>();
	this->texture->create(image);
	return true;
}

