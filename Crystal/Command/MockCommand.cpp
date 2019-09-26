#include "MockCommand.h"

using namespace Crystal::Command;

void MockCommand::execute()
{
	auto v1 = args.lhs.getValue();
	results.value = args.lhs.getValue() + args.rhs.getValue();
}