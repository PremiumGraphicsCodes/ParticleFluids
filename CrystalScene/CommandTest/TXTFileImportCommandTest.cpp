#include "pch.h"

#include "../Command/TXTFileImportCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(TXTFileImportCommandTest, TestWriteJSON)
{
	TXTFileImportCommand command;
	command.writeJSON("TXTFileImportWrite.json");
}

TEST(TXTFileImportCommandTest, TestReadJSON)
{
	TXTFileImportCommand command;
	command.readJSON("TXTFileImportWrite.json");
}