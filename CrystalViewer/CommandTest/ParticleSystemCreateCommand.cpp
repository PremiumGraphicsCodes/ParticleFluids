#include "pch.h"

#include "../Command/CommandFactory.h"

#include "../Command/Public/ParticleSystemCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(ParticleSystemCreateCommand, TestExecute)
{
	World world;
	CommandFactory factory;

	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	auto command = factory.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command->setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	EXPECT_TRUE( command->execute(&world) );

	const auto newId = std::any_cast<int>(command->getResult(ParticleSystemCreateLabels::NewIdLabel));
	EXPECT_EQ(1, newId);
}