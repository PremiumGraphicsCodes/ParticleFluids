#include "pch.h"

#include "../Command/Command.h"

using namespace Crystal::Command;

TEST(CommandTest, TestExecute)
{
	Crystal::Scene::Scene scene(0, "");
	Command command("Mock");
	command.setArg("lhs", 1);
	command.setArg("rhs", 2);
	command.execute(&scene);
	const auto actual = std::any_cast<int>( command.getResult("value") );
	EXPECT_EQ( 3, actual );
}