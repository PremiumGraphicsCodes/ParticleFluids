#include "TextureObjectRepository.h"

#include "../Shader/TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

TextureObjectRepository::TextureObjectRepository() :
	nextId(1)
{
}

TextureObjectRepository::~TextureObjectRepository()
{
	clear();
}

void TextureObjectRepository::clear()
{
	for (auto t : textures) {
		t.clear();
	}
	textures.clear();
}

void TextureObjectRepository::add(const TextureObject& texture, const std::string& name)
{
	textures.push_back(texture);
}
