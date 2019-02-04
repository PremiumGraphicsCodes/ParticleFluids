#pragma once

#include "ObjectViewModel.h"
#include "ObjectIdViewModel.h"
#include "AppearanceViewModel.h"

namespace Crystal {
	namespace UI {

class ViewModel
{
public:
	ViewModel() {}

	ObjectViewModel* getObject() { return &objectVM; }

	ObjectIdViewModel* getObjectId() { return &objectIdVM; }

	AppearanceViewModel* getAppearance() { return &appearanceVM; }

private:
	ObjectViewModel objectVM;
	ObjectIdViewModel objectIdVM;
	AppearanceViewModel appearanceVM;
};
	}
}