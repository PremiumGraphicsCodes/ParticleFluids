#include "pch.h"
#include "stdlib.h"
#include "Sample.h"
#include <cstring>

#include "CrystalScene/Command/CommandFactory.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsCommandFactory.h"

namespace {
	std::unique_ptr<Crystal::Command::ICommand> command;
	Crystal::Command::CommandFactory factory;
	Crystal::Physics::PhysicsCommandFactory physicsFactory;
	Crystal::Scene::World world;
}

SAMPLE_API void CreateCommand(const char* str)
{
	::command = Crystal::Command::CommandFactory::create(str);
}

SAMPLE_API void CreatePhysicsCommand(const char* str)
{
	::command = Crystal::Physics::PhysicsCommandFactory::create( str );
}

SAMPLE_API void SetArgInt(const char* name, int i)
{
	::command->setArg(name, i);
}

SAMPLE_API void SetArgFloat(const char* name, float f)
{
	::command->setArg(name, f);
}

SAMPLE_API void SetArgDouble(const char* name, double d)
{
	::command->setArg(name, d);
}

SAMPLE_API void SetArgString(const char* name, const char* str)
{
	::command->setArg(name, str);
}

SAMPLE_API int Execute()
{
	::command->execute(&world);
	return 1;
}

SAMPLE_API int GetResultInt(const char* name)
{
	return std::any_cast<int>( ::command->getResult(name) );
}
