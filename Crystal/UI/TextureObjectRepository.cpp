#include "TextureObjectRepository.h"

using namespace Crystal::Graphics;
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

/*
void TextureObjectRepository::add(Material* m, const std::string& name)
{
	MaterialObject material(nextId++, name, m);
	materials.push_back(material);
}
*/
