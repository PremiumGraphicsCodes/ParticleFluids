#include "pch.h"

#include "../Command/TXTFileExportCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(TXTFileExportCommandTest, TestWriteJSON)
{
	TXTFileExportCommand command;
	command.writeJSON("TXTFileExportWrite.json");
}

TEST(TXTFileExportCommandTest, TestReadJSON)
{
	TXTFileExportCommand command;
	command.readJSON("TXTFileExportWrite.json");
}