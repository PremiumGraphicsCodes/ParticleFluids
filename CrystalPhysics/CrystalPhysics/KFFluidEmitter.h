#pragma once

#include <vector>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Physics {

class KFFluidEmitter
{
public:
	void addSource(const Math::Vector3df& p) { this->positions.push_back(p); }

	void setStartEnd(const int startStep, const int endStep) { this->startEndStep = std::make_pair(startStep, endStep); }

	std::vector<Math::Vector3df> getPositions() const { return positions; }

	int getStartStep() const { return startEndStep.first; }

	int getEndStep() const { return startEndStep.second; }

private:
	std::vector<Math::Vector3df> positions;
	std::pair<int,int> startEndStep;
};

	}
}