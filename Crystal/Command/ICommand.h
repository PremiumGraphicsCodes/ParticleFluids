#pragma once

#include "../Util/UnCopyable.h"
#include "IArgs.h"
#include "IResults.h"

namespace Crystal {
	namespace Command {

class ICommand : private UnCopyable
{
public:
	ICommand(IArgs* args, IResults* results) :
		args(args),
		results(results)
	{}

	virtual ~ICommand(){}

	void setArg(const std::string& name, std::any value) { args->setValue(name, value); }

	virtual void execute() = 0;

	std::any getResult(const std::string& name) { return results->getValue(name); }

private:
	IArgs* args;
	IResults* results;
};
	}
}