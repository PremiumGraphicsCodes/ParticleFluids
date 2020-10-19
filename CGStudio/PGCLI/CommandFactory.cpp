#include "stdafx.h"
#include "CommandFactory.h"

#include "../../CrystalViewer/Command/CommandFactory.h"
#include "Converter.h"
#include "EachCommand.h"

using namespace PG::CLI;

namespace {
	Crystal::Command::CommandFactory instance;
}

EachCommand^ CommandFactory::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	return gcnew EachCommand( ::instance.createCommand(str) );
}
