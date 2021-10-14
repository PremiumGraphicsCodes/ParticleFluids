#include "pch.h"

#include "../Command/STLFileExportCommand.h"


using namespace Crystal::Command;

TEST(STLFileExportCommandTest, TestWriteJSON)
{
	STLFileExportCommand command;
	command.writeJSON("STLFileExportWrite.json");
}