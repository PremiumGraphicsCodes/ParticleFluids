#include "pch.h"

#include "../Command/FileExportCommand.h"

using namespace Crystal::Command;

TEST(FileExportCommand, TestWriteJSON)
{
	FileExportCommand command;
	command.writeJSON("FileExport.json");
}

TEST(FileExportCommand, TestReadJSON)
{
	FileExportCommand command;
	command.readJSON("FileExport.json");
}