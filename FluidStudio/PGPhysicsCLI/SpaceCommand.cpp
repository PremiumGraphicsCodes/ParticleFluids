#include "stdafx.h"
#include "SpaceCommand.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalSpace/CrystalSpaceCommand/SpaceCommandFactory.h"

//#include "../../Crystal/Scene/World.h"
#include "../PGCLI/Converter.h"
#include "../PGCLI/AnyConverter.h"
//#include "../PGCLI/WorldAdapter.h"

using namespace PG::CLI;

namespace {
	std::unique_ptr<Crystal::Command::ICommand> space_instance;
	Crystal::Space::SpaceCommandFactory factory;
}

SpaceCommand::SpaceCommand()
{}

SpaceCommand::SpaceCommand(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::space_instance = factory.create(str);
}

void SpaceCommand::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::space_instance = factory.create(str);
}

generic <class T>
void SpaceCommand::SetArg(System::String^ name, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	const auto v = AnyConverter::toCpp(value, T::typeid);
	::space_instance->setArg(str, v);
}

bool SpaceCommand::Execute(WorldAdapter^ objects)
{
	auto world = static_cast<Crystal::Scene::World*>(objects->getPtr().ToPointer());
	return ::space_instance->execute(world);
}

generic <class T>
T SpaceCommand::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::space_instance->getResult(str);
	return (T)(AnyConverter::fromCpp(result));
}

void SpaceCommand::Clear()
{
	::space_instance.reset();
}