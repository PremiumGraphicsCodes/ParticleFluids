#pragma once

#include "ObjectViewModel.h"
#include "ObjectIdViewModel.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class ViewModel// : private UnCopyable
{
public:
	ViewModel() {}

	ObjectViewModel object;
	ObjectIdViewModel objectId;
};
	}
}