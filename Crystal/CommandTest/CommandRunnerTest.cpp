#include "pch.h"

#include "../Command/CommandRunner.h"

using namespace Crystal::Command;

TEST(CommandRunnerTest, TestExecute)
{
	CommandRunner runner;
	runner.create("Mock");
	runner.setArg("lhs", 1);
	runner.setArg("rhs", 2);
	runner.execute();
	const auto actual = std::any_cast<int>( runner.getResult("value") );
	EXPECT_EQ( 3, actual );
//	auto actual = Command::create("Mock");
//	EXPECT_NE(nullptr, actual);
}