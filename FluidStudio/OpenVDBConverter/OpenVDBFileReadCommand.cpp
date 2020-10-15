#include "OpenVDBFileReadCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::OpenVDB;

OpenVDBFileReadCommand::Args::Args() :
	filePath("FilePath", "")
{
	add(&filePath);
}

OpenVDBFileReadCommand::Results::Results() :
	newId("NewId", -1)
{
	add(&newId);
}

OpenVDBFileReadCommand::OpenVDBFileReadCommand() :
	ICommand(&args, &results)
{}

std::string OpenVDBFileReadCommand::getName()
{
	return "OpenVDBFileRead";
}

bool OpenVDBFileReadCommand::execute(World* world)
{
	return false;
}

