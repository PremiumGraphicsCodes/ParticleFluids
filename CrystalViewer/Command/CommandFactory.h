#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CommandFactory : UnCopyable
{
public:
	static std::unique_ptr<ICommand> create(const std::string& name);

	std::unique_ptr<ICommand> createCommand(const std::string& name) {
		return create(name);
	}
};
	}
}