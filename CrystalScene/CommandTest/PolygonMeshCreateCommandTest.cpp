#include "pch.h"

#include "../Command/PolygonMeshCreateCommand.h"

using namespace Crystal::Command;

TEST(PolygonMeshCreateCommandTest, TestWriteJSON)
{
	PolygonMeshCreateCommand command;
	command.writeJSON("PolygonMeshCreateWrite.json");
}

TEST(PolygonMeshCreateCommandTest, TestReadJSON)
{
	PolygonMeshCreateCommand command;
	command.readJSON("PolygonMeshCreateWrite.json");
}