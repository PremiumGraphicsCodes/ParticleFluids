#include "ImageObjectRepository.h"

#include "ImageObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

ImageObjectRepository::ImageObjectRepository() :
	nextId(1)
{
}

ImageObjectRepository::~ImageObjectRepository()
{
	clear();
}

void ImageObjectRepository::clear()
{
	for (auto t : images) {
		delete t->getImage();
		delete t;
	}
	images.clear();
	this->nextId = 1;
}

void ImageObjectRepository::add(const Image& image, const std::string& name)
{
	auto object = new ImageObject(this->nextId, name, image.clone());
	images.push_back(object);
}

ImageObject* ImageObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(images), std::cend(images), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(images)) {
		return nullptr;
	}
	return *iter;
}