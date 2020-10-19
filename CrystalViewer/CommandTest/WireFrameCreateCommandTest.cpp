#include "pch.h"

#include "../Command/Command.h"
#include "../Command/CommandFactory.h"

#include "../Command/Public/WireFrameCreateLabels.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(WireFrameCreateCommandTest, TestExecute)
{
	World world;

	WireFrameBuilder builder;
	builder.build(Line3dd(Vector3dd(0,0,0), Vector3dd(1,0,0)));

	auto command = CommandFactory::create(WireFrameCreateLabels::WireFrameAddLabel);
	command->setArg(WireFrameCreateLabels::PositionsLabel, builder.getPositions());
	command->setArg(WireFrameCreateLabels::EdgesLabel, builder.getEdges());
	EXPECT_TRUE(command->execute(&world));

	const auto newId = std::any_cast<int>(command->getResult(WireFrameCreateLabels::NewIdLabel));
	EXPECT_EQ(1, newId);
}