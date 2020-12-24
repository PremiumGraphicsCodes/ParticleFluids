#include "TextureShaderScene.h"

#include "ITextureScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void TextureShaderScene::update(const int index)
{
	for (auto s : parentScenes) {
		s->sendTexture(index, *textures[index]);
	}
}