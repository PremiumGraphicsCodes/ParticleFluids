#pragma once

#include "../Util/UnCopyable.h"
#include "LightObjectRepository.h"
#include "MaterialObjectRepository.h"

namespace Crystal {
	namespace UI {

class AppearanceObjectRepository : private UnCopyable
{
public:
	AppearanceObjectRepository()
	{}

	~AppearanceObjectRepository()
	{

	}

	void clear() {
		lights.clear();
		materials.clear();
	}

	LightObjectRepository* getLights() { return &lights; }

	MaterialObjectRepository* getMaterials() { return &materials; }

private:
	LightObjectRepository lights;
	MaterialObjectRepository materials;
};
	}
}