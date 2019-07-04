#pragma once

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {

class SceneIdProvider : private UnCopyable
{
public:
	SceneIdProvider() :
		nextId(1)
	{}

	int getNextId() { return nextId++; }

	void reset() { this->nextId = 1; }

private:
	int nextId;
};
	}
}