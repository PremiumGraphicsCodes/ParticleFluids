#include "pch.h"

#include "../Command/PolygonMeshCreateCommand.h"

using namespace Crystal::Command;

TEST(PolygonMeshCreateCommandTest, TestWriteJSON)
{
	PolygonMeshCreateCommand command;
	command.writeJSON("PolygonMeshCreateWrite.json");
}