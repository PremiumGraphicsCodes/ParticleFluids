#pragma once

#include "../Util/UnCopyable.h"
#include "IArgs.h"
#include <any>
#include <string>
#include <map>
#include <vector>

namespace Crystal {
	namespace Command {

struct IResult
{
	std::string name;
	std::any value;
};

struct IResults
{
//	std::map<std::string, std::any> results;
};

class ICommand : private UnCopyable
{
public:
	void setArg(const std::string& name, std::any value) { args->setValue(name, value); }

	virtual void execute() = 0;

	//std::any getResult(std::string& name) { return args[name]; }

	ICommand(IArgs* args, IResults* results) :
		args(args),
		results(results)
	{}

private:
	IArgs* args;
	IResults* results;
};
	}
}