#include "stdafx.h"
#include "VDBCommand.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../FluidStudio/VDBCommand/VDBCommandFactory.h"

//#include "../../Crystal/Scene/World.h"
#include "../PGCLI/Converter.h"
#include "../PGCLI/AnyConverter.h"
//#include "../PGCLI/WorldAdapter.h"

using namespace PG::CLI;

namespace {
	std::unique_ptr<Crystal::Command::ICommand> instance;
	Crystal::OpenVDB::VDBCommandFactory factory;
}

VDBCommand::VDBCommand()
{}

VDBCommand::VDBCommand(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance = factory.createCommand(str);
}

void VDBCommand::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance = factory.createCommand(str);
}

generic <class T>
void VDBCommand::SetArg(System::String^ name, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	const auto v = AnyConverter::toCpp(value, T::typeid);
	::instance->setArg(str, v);
}

bool VDBCommand::Execute(WorldAdapter^ objects)
{
	auto world = static_cast<Crystal::Scene::World*>(objects->getPtr().ToPointer());
	return ::instance->execute(world);
}

generic <class T>
T VDBCommand::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::instance->getResult(str);
	return (T)(AnyConverter::fromCpp(result));
}

void VDBCommand::Clear()
{
	::instance.reset();
}