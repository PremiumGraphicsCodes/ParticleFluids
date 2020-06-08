#pragma once

namespace Crystal {
	namespace Scene{

class IAnimator
{
public:
	virtual void step() = 0;
};
	}
}