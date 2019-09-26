#include "MockCommand.h"

using namespace Crystal::Command;

void MockCommand::execute()
{
	results.value = args.lhs + args.rhs;
}