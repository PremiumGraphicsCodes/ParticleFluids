#include "stdafx.h"
#include "PhysicsCommand.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalPhysics/CrystalPhysicsCommand/PhysicsCommandFactory.h"

//#include "../../Crystal/Scene/World.h"
#include "../PGCLI/Converter.h"
#include "../PGCLI/AnyConverter.h"
//#include "../PGCLI/WorldAdapter.h"

using namespace PG::CLI;

namespace {
	std::unique_ptr<Crystal::Command::ICommand> physics_instance;
	Crystal::Physics::PhysicsCommandFactory factory;
}

PhysicsCommand::PhysicsCommand()
{}

PhysicsCommand::PhysicsCommand(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::physics_instance = factory.create(str);
}

void PhysicsCommand::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::physics_instance = factory.create(str);
}

generic <class T>
void PhysicsCommand::SetArg(System::String^ name, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	const auto v = AnyConverter::toCpp(value, T::typeid);
	::physics_instance->setArg(str, v);
}

bool PhysicsCommand::Execute(WorldAdapter^ objects)
{
	auto world = static_cast<Crystal::Scene::World*>( objects->getPtr().ToPointer() );
	return ::physics_instance->execute(world);
}

generic <class T>
T PhysicsCommand::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::physics_instance->getResult(str);
	return (T)(AnyConverter::fromCpp(result));
}

void PhysicsCommand::Clear()
{
	::physics_instance.reset();
}