#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "PropertyTree.h"

namespace Crystal {
	namespace Command {

class ILabeledValueFactory : UnCopyable
{
public:
	virtual std::unique_ptr<PropertyTree> create(const std::string& name) const = 0;
};

	}
}