#pragma once

#include "../Util/UnCopyable.h"
#include <any>
#include <string>
#include <map>

namespace Crystal {
	namespace Command {

struct IArgs
{
//	std::map<std::string, std::any> args;
};

struct IResults
{
//	std::map<std::string, std::any> results;
};

class ICommand : private UnCopyable
{
public:
	//void setArg(std::string& name, std::any value) { args[name] = value; }

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