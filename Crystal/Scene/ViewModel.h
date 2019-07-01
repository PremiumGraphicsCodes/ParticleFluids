#pragma once

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

namespace Crystal {
	namespace UI {

class ViewModel
{
public:
	ViewModel() {}

	SceneViewModel object;
	SceneIdViewModel objectId;
};
	}
}