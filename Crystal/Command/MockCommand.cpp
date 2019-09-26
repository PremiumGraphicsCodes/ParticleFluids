#include "MockCommand.h"

using namespace Crystal::Command;

void MockCommand::execute()
{
	results.value.setValue( args.lhs.getValue() + args.rhs.getValue() );
}