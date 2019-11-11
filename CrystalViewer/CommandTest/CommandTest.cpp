#include "pch.h"

#include "../Command/Command.h"

using namespace Crystal::Command;

TEST(CommandTest, TestExecute)
{
	Crystal::Scene::World world;
	Command command("Mock");
	command.setArg("lhs", 1);
	command.setArg("rhs", 2);

	EXPECT_EQ( typeid(int), command.getArgType("lhs") );
	EXPECT_EQ( typeid(int), command.getArgType("rhs"));

	command.execute(&world);
	const auto actual = std::any_cast<int>( command.getResult("value") );
	EXPECT_EQ( 3, actual );
}