#include "TextureObjectRepository.h"

#include "TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TextureObjectRepository::TextureObjectRepository() :
	nextId(1),
	onScreenTexture(nullptr)
{
}

TextureObjectRepository::~TextureObjectRepository()
{
	clear();
}

void TextureObjectRepository::clear()
{
	for (auto t : textures) {
		t->clear();
		delete t;
	}
	textures.clear();
	this->nextId = 1;
}

int TextureObjectRepository::add(const Image& image, const std::string& name)
{
	auto texture = new Crystal::Shader::TextureObject();
	texture->create(image, nextId++);
	texture->setName(name);
	textures.push_back(texture);
	return texture->getId();
}

TextureObject* TextureObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(textures), std::cend(textures), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(textures)) {
		return nullptr;
	}
	return *iter;
}