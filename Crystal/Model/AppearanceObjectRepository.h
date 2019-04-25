#pragma once

#include "../Util/UnCopyable.h"
#include "LightObjectRepository.h"
#include "MaterialObjectRepository.h"
#include "ImageObjectRepository.h"
#include "TextureObjectRepository.h"

namespace Crystal {
	namespace Model {

class AppearanceObjectRepository : private UnCopyable
{
public:
	AppearanceObjectRepository()
	{}

	~AppearanceObjectRepository()
	{}

	void clear();

	LightObjectRepository* getLights() { return &lights; }

	MaterialObjectRepository* getMaterials() { return &materials; }

	ImageObjectRepository* getImages() { return &images; }

	TextureObjectRepository* getTextures() { return &textures; }

private:
	LightObjectRepository lights;
	MaterialObjectRepository materials;
	ImageObjectRepository images;
	TextureObjectRepository textures;
};
	}
}