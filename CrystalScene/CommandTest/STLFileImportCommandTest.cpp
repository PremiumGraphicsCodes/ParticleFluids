#include "pch.h"

#include "../Command/STLFileImportCommand.h"

using namespace Crystal::Command;

TEST(STLFileImportCommand, TestWriteJSON)
{
	STLFileImportCommand command;
	command.writeJSON("STLFileImportWrite.json");
}

TEST(STLFileImportCommand, TestReadJSON)
{
	STLFileImportCommand command;
	command.readJSON("STLFileImportWrite.json");
}