#pragma once

#include "SceneViewModel.h"
#include "ObjectIdViewModel.h"

namespace Crystal {
	namespace UI {

class ViewModel
{
public:
	ViewModel() {}

	SceneViewModel object;
	ObjectIdViewModel objectId;
};
	}
}