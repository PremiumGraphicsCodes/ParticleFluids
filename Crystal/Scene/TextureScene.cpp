#include "TextureScene.h"

#include "../Shader/TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureScene::TextureScene(const int id, std::unique_ptr<Image> image, const std::string& name) :
	IScene(id, name),
	image(std::move(image))
{
}