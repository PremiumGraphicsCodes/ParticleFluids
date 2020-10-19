#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CommandFactory : UnCopyable
{
public:
	static std::unique_ptr<ICommand> create(const std::string& name);
};
	}
}