#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "LabeledValueTree.h"

namespace Crystal {
	namespace Command {

class ILabeledValueFactory : UnCopyable
{
public:
	virtual std::unique_ptr<LabeledValueTree> create(const std::string& name) const = 0;
};

	}
}