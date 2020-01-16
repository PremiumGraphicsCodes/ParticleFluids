#include "TextureScene.h"

#include "../Shader/TextureObject.h"
#include "SceneViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureScene::TextureScene(const int id, const TextureObject& texture, const std::string& name, const Image& image) :
	IScene(id, name),
	image(image),
	texture(texture)
{
}

void TextureScene::onClear()
{
	texture.clear();
};

void TextureScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.textures.push_back(texture);
}