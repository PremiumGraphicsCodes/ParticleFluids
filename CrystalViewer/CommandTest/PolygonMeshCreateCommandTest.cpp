#include "pch.h"

#include "../Command/Command.h"

#include "../Command/Public/PolygonMeshCreateLabels.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PolygonMeshCreateCommandTest, TestExecute)
{
	World world;

	PolygonMeshBuilder builder;
	builder.add(Box3d());

	Crystal::Command::Command command(PolygonMeshCreateLabels::CommandNameLabel);
	command.setArg(PolygonMeshCreateLabels::PositionsLabel, builder.getPositions());
	command.setArg(PolygonMeshCreateLabels::VerticesLabel, builder.getVertices());
	command.setArg(PolygonMeshCreateLabels::NormalsLabel, builder.getNormals());
	command.setArg(PolygonMeshCreateLabels::TexCoordsLabel, builder.getTexCoords());
	command.setArg(PolygonMeshCreateLabels::FacesLabel, builder.getFaces());
	EXPECT_TRUE(command.execute(&world));

	const auto newId = std::any_cast<int>(command.getResult(PolygonMeshCreateLabels::NewIdLabel));
	EXPECT_EQ(1, newId);
}