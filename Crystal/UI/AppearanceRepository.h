#pragma once

#include "../Util/UnCopyable.h"
#include "LightRepository.h"
#include "MaterialRepository.h"

namespace Crystal {
	namespace UI {

class AppearanceObjectRepository : private UnCopyable
{
public:
	AppearanceObjectRepository()
	{}

	~AppearanceObjectRepository();

	void clear();

private:
};
	}
}