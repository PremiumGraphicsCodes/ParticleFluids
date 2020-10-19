#include "stdafx.h"
#include "PhysicsCommand.h"

#include "../../CrystalViewer/Command/Command.h"

//#include "../../Crystal/Scene/World.h"
#include "../PGCLI/Converter.h"
#include "../PGCLI/AnyConverter.h"
//#include "../PGCLI/WorldAdapter.h"

using namespace PG::CLI;

/*
namespace {
	Crystal::Command::Command instance;
}
*/

PhysicsCommand::PhysicsCommand()
{}

PhysicsCommand::PhysicsCommand(System::String^ name)
{
	command->Create(name);
	//const auto& str = Converter::toCpp(name);
	//::instance.create(str);
}

void PhysicsCommand::Create(System::String^ name)
{
	command->Create(name);
	//const auto& str = Converter::toCpp(name);
	//::instance.create(str);
}

generic <class T>
void PhysicsCommand::SetArg(System::String^ name, T value)
{
	command->SetArg(name, value);
	//const auto& str = PG::CLI::Converter::toCpp(name);
	//const auto v = AnyConverter::toCpp(value, T::typeid);
	//::instance.setArg(str, v);
}

bool PhysicsCommand::Execute(WorldAdapter^ objects)
{
	auto world = static_cast<Crystal::Scene::World*>( objects->getPtr().ToPointer() );
	return command->Execute(objects);
	//return ::instance.execute(objects->instance);
}

generic <class T>
T PhysicsCommand::GetResult(System::String^ name)
{
	return command->GetResult<T>(name);
	//const auto& str = msclr::interop::marshal_as<std::string>(name);
	//auto result = ::instance.getResult(str);
	//return (T)(AnyConverter::fromCpp(result));
}

void PhysicsCommand::Clear()
{
	command->Clear();
	//::instance.clear();
}