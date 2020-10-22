#include "stdafx.h"
#include "PhysicsCommand.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalAlgo/CrystalPhysicsCommand/PhysicsCommandFactory.h"

//#include "../../Crystal/Scene/World.h"
#include "../PGCLI/Converter.h"
#include "../PGCLI/AnyConverter.h"
//#include "../PGCLI/WorldAdapter.h"

using namespace PG::CLI;

namespace {
	std::unique_ptr<Crystal::Command::ICommand> instance;
	Crystal::Physics::PhysicsCommandFactory factory;
}

PhysicsCommand::PhysicsCommand()
{}

PhysicsCommand::PhysicsCommand(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance = factory.create(str);
}

void PhysicsCommand::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance = factory.create(str);
}

generic <class T>
void PhysicsCommand::SetArg(System::String^ name, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	const auto v = AnyConverter::toCpp(value, T::typeid);
	::instance->setArg(str, v);
}

bool PhysicsCommand::Execute(WorldAdapter^ objects)
{
	auto world = static_cast<Crystal::Scene::World*>( objects->getPtr().ToPointer() );
	return ::instance->execute(world);
}

generic <class T>
T PhysicsCommand::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::instance->getResult(str);
	return (T)(AnyConverter::fromCpp(result));
}

void PhysicsCommand::Clear()
{
	::instance.reset();
}