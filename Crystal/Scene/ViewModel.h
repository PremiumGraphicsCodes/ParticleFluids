#pragma once

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

namespace Crystal {
	namespace Scene {

class ViewModel
{
public:
	SceneViewModel object;
	SceneIdViewModel parentId;
	SceneIdViewModel childId;
};
	}
}