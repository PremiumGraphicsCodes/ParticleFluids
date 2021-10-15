#include "pch.h"

#include "../Command/WireFrameCreateCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(WireFrameCreateCommandTest, TestWriteJSON)
{
	WireFrameCreateCommand command;
	command.writeJSON("WireFrameCreateWrite.json");
}

TEST(WireFrameCreateCommandTest, TestReadJSON)
{
	WireFrameCreateCommand command;
	command.readJSON("WireFrameCreateWrite.json");
}