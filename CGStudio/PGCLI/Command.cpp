#include "stdafx.h"
#include "Command.h"

#include <msclr/marshal_cppstd.h>

#include "../../Crystal/Command/CommandRunner.h"

using namespace PG::CLI;
using namespace Crystal::Command;

namespace {
	CommandRunner instance;
}

Command::Command(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	::instance.create(str);
}

void Command::SetArg(System::String^ name, System::Object^ value)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	//::instance.setArg(str,);
}

void Command::Execute()
{
	::instance.execute();
}


void Command::Clear()
{
	//instance.clear();
}
