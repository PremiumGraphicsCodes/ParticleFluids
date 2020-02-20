#include "pch.h"

#include "../Command/Command.h"

#include "../Command/Public/WireFrameCreateLabels.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(WireFrameCreateCommandTest, TestExecute)
{
	World world;

	WireFrameBuilder builder;
	//builder.build();

	/*
	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0), Vector3dd(1,0,0) };
	Crystal::Command::Command command(WireFrameCreateLabels::WireFrameAddLabel);
	command.setArg(WireFrameCreateLabels::PositionsLabel, positions);
	command.setArg(WireFrameCreateLabels::EdgesLabel,)
	EXPECT_TRUE(command.execute(&world));

	const auto newId = std::any_cast<int>(command.getResult(WireFrameCreateLabels::NewIdLabel));
	EXPECT_EQ(1, newId);
		*/

}