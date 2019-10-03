#pragma once

#include "../Util/UnCopyable.h"
#include "IArgs.h"
#include "IResults.h"

#include "../Scene/World.h"

namespace Crystal {
	namespace Command {

class ICommand : private UnCopyable
{
public:
	ICommand() :
		args(nullptr),
		results(nullptr)
	{}

	explicit ICommand(IArgs* args) :
		args(args),
		results(nullptr)
	{}

	ICommand(IArgs* args, IResults* results) :
		args(args),
		results(results)
	{}

	virtual ~ICommand(){}

	void setArg(const std::string& name, std::any value) { args->setValue(name, value); }

	virtual void execute(Scene::World* scene) = 0;

	std::any getResult(const std::string& name) { return results->getValue(name); }

private:
	IArgs* args;
	IResults* results;
};
	}
}