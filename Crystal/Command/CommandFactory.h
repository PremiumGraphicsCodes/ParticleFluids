#pragma once

#include "../Util/UnCopyable.h"
#include "ICommand.h"
#include <map>
#include <memory>

namespace Crystal {
	namespace Command {

class CommandFactory : UnCopyable
{
public:
	static std::unique_ptr<ICommand> create(const std::string& name);
};
	}
}