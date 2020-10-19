#include "CommandFactory.h"

#include "../../CrystalViewer/Command/CommandFactory.h"
#include "Converter.h"

using namespace PG::CLI;

namespace {
	Crystal::Command::CommandFactory instance;
}

Command^ CommandFactory::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	return ::instance.createCommand(str);
}
