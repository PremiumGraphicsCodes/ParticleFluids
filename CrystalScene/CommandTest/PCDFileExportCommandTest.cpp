#include "pch.h"

#include "../Command/Command.h"
#include "../Command/PCDFileExportCommand.h"

#include "../Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileExportCommandTest, TestWriteJSON)
{
	PCDFileExportCommand command;
	command.writeJSON("PCDFileExportCommandWrite.json");
}

TEST(PCDFileExportCommandTest, TestReadJSON)
{
	PCDFileExportCommand command;
	command.readJSON("PCDFileExportCommandWrite.json");
}