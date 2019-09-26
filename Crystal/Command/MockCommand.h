#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MockCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Arg<int> lhs;
		Arg<int> rhs;

		Args() :
			lhs("lhs", 0),
			rhs("rhs", 0)
		{
			add(&lhs);
			add(&rhs);
		}
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