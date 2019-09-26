#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MockCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		int lhs;
		int rhs;
	};

	struct Results : IResults
	{
		int value;
	};

	MockCommand() :
		ICommand(&args, &results)
	{}

	void execute();

private:
	Args args;
	Results results;
};
	}
}