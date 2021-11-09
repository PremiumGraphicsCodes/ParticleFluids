#include "pch.h"

#include "../Command/STLFileImportCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(STLFileImportCommandTest, TestWriteJSON)
{
	STLFileImportCommand command;
	command.writeJSON("STLFileImportWrite.json");
}

TEST(STLFileImportCommandTest, TestReadJSON)
{
	STLFileImportCommand command;
	command.readJSON("STLFileImportWrite.json");
}

/*
TEST(STLFileImportCommandTest, TestExecute)
{
	STLFileImportCommand command;
	command.setArg("Id", 1)
}
*/