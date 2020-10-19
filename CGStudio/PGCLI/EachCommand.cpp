#include "stdafx.h"
#include "../../CrystalViewer/Command/ICommand.h"
#include "EachCommand.h"

using namespace PG::CLI;

namespace {
	std::unique_ptr<Crystal::Command::ICommand> instance;
}

EachCommand::EachCommand(std::unique_ptr<Crystal::Command::ICommand> instance)
{
	::instance = std::move(instance);
}

std::unique_ptr<Crystal::Command::ICommand> EachCommand::getInstance()
{
	return std::move(::instance);
}
