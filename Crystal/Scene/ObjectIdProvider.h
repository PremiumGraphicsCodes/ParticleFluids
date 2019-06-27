#pragma once

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Model {

class ObjectIdProvider : private UnCopyable
{
public:
	ObjectIdProvider() :
		nextId(1)
	{}

	int getNextId() { return nextId++; }

	void reset() { this->nextId = 1; }

private:
	int nextId;
};
	}
}