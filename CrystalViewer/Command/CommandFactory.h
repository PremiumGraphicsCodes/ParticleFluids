#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class ICommandFactory : UnCopyable
{
public:
	virtual std::unique_ptr<ICommand> createCommand(const std::string& name) = 0;
};

class CommandFactory : public ICommandFactory
{
public:
	static std::unique_ptr<ICommand> create(const std::string& name);

	std::unique_ptr<ICommand> createCommand(const std::string& name) override {
		return create(name);
	}
};
	}
}