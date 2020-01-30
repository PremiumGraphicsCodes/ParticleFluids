#include "TextureScene.h"

#include "../Shader/TextureObject.h"
#include "SceneViewModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureScene::TextureScene(const int id, const Image& image, const std::string& name) :
	IScene(id, name),
	image(image)
{
}

void TextureScene::onClear()
{
};

void TextureScene::onBuild(GLObjectFactory& factory)
{
	texture = factory.getTextureFactory()->createTextureObject(image);
}

void TextureScene::toViewModel(SceneViewModel& viewModel) const
{
	viewModel.textures.push_back(*texture);
}

void TextureScene::update(const Image& image)
{
	texture->send(image);
}
