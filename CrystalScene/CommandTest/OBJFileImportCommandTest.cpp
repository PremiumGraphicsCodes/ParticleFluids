#include "pch.h"

#include "../Command/OBJFileImportCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(OBJFileImportCommandTest, TestWriteJSON)
{
	OBJFileImportCommand command;
	command.writeJSON("OBJFileImportCommandWrite.json");
}

TEST(OBJFileImportCommandTest, TestReadJSON)
{
	OBJFileImportCommand command;
	command.readJSON("OBJFileImportCommandWrite.json");
}