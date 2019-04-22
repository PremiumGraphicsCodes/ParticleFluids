#include "TextureObjectRepository.h"

#include "TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

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
		t->getTexture()->clear();
		delete t;
	}
	textures.clear();
	this->nextId = 1;
}

void TextureObjectRepository::add(const Image& image, const std::string& name)
{
	Crystal::Shader::TextureObject* texture = new Crystal::Shader::TextureObject();
	texture->create(image, nextId++);
	TextureObject* object = new TextureObject(texture->getId(), name, texture);
	textures.push_back(object);
}

TextureObject* TextureObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(textures), std::cend(textures), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(textures)) {
		return nullptr;
	}
	return *iter;
}