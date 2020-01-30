#include "TextureScene.h"

#include "../Shader/TextureObject.h"
#include "SceneViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureScene::TextureScene(const int id, const TextureObject& texture, const std::string& name) :
	IScene(id, name),
	texture(texture)
{
}

void TextureScene::onClear()
{
	texture.clear();
};

void TextureScene::onBuild(GLObjectFactory& factory)
{

}

void TextureScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.textures.push_back(texture);
}

void TextureScene::update(const Image& image)
{
	texture.send(image);
}
