#pragma once

#include "../Util/UnCopyable.h"
#include "MaterialObjectRepository.h"
#include "ImageObjectRepository.h"

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


	MaterialObjectRepository* getMaterials() { return &materials; }

	ImageObjectRepository* getImages() { return &images; }

private:
	MaterialObjectRepository materials;
	ImageObjectRepository images;
};
	}
}