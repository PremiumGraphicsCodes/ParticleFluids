#include "pch.h"

#include "../Command/ParticleSystemCreateCommand.h"
#include "../Command/CommandFactory.h"

using namespace Crystal::Command;

TEST(ParticleSystemCreateCommandTest, TestExecute)
{
	ParticleSystemCreateCommand command;
	command.writeJSON("ParticleSystemCreateCommandWrite.json");
}