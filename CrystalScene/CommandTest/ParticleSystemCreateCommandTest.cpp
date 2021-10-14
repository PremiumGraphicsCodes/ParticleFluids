#include "pch.h"

#include "../Command/ParticleSystemCreateCommand.h"
#include "../Command/CommandFactory.h"

using namespace Crystal::Command;

TEST(ParticleSystemCreateCommandTest, TestWriteJSON)
{
	ParticleSystemCreateCommand command;
	command.writeJSON("ParticleSystemCreateCommandWrite.json");
}

TEST(ParticleSystemCreateCommandTest, TestReadJSON)
{
	ParticleSystemCreateCommand command;
	command.readJSON("ParticleSystemCreateCommandWrite.json");
}