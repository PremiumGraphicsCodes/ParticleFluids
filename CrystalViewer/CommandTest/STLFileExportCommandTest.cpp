#include "pch.h"

#include "../Command/Command.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "../Command/Public/STLFileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(STLFileExportCommandTest, TestExecute)
{
	World world;

	PolygonMeshBuilder builder;
	builder.add(Box3d());
	auto scene = new PolygonMeshScene(1, "", builder.build());
	world.getScenes()->addScene(scene);

	const std::vector<int> newIds = { scene->getId() };
	const std::string filePath = "STLFileExportTest.stl";
	Command command(STLFileExportLabels::CommandNameLabel);
	command.setArg(STLFileExportLabels::IdsLabel, newIds);
	command.setArg(STLFileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE(command.execute(&world));
}