#include "pch.h"

#include "../Command/PCDFileImportCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileImportCommandTest, TestWriteJSON)
{
	PCDFileImportCommand command;
	command.writeJSON("PCDFileImportWrite.json");
}

TEST(PCDFileImportCommandTest, TestReadJSON)
{
	PCDFileImportCommand command;
	command.readJSON("PCDFileImportWrite.json");
}