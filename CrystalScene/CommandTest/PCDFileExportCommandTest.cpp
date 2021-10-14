#include "pch.h"

#include "../Command/Command.h"
#include "../Command/PCDFileExportCommand.h"

#include "../Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileExportCommand, TestWriteJSON)
{
	PCDFileExportCommand command;
	command.writeJSON("PCDFileExportCommandWrite.json");
}

TEST(PCDFileExportCommand, TestReadJSON)
{
	PCDFileExportCommand command;
	command.readJSON("PCDFileExportCommandWrite.json");
}