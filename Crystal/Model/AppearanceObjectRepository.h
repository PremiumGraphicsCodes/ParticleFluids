#pragma once

#include "../Util/UnCopyable.h"
#include "LightObjectRepository.h"
#include "MaterialObjectRepository.h"
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

	TextureObjectRepository* getTextures() { return &textures; }

private:
	LightObjectRepository lights;
	MaterialObjectRepository materials;
	TextureObjectRepository textures;
};
	}
}