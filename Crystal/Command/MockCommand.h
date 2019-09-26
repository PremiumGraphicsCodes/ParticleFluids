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

	void execute();

	struct Results : IResults
	{
		int value;
	};

private:
	Args args;
	Results results;
};
	}
}