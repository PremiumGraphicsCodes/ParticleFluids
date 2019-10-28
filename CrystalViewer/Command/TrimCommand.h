#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class TrimCommand : public ICommand
{
	struct Args : IArgs
	{
		Arg<int> shapeId;
//		Arg<Region> region;
	};

private:

};

	}
}