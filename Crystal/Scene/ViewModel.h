#pragma once

#include "ObjectViewModel.h"
#include "ObjectIdViewModel.h"

namespace Crystal {
	namespace UI {

class ViewModel
{
public:
	ViewModel() {}

	ObjectViewModel object;
	ObjectIdViewModel objectId;
};
	}
}