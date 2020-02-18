#include "pch.h"

#include "../Command/Command.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(STLFileExportCommandTest, TestExecute)
{
	World world;

	PolygonMeshBuilder builder;
	builder.add(Box3d());
	auto scene = world.getSceneFactory()->createPolygonMeshScene(builder.build(), "");
	world.getObjects()->addScene(scene);

	const std::vector<int> newIds = { scene->getId() };
	const std::string filePath = "./STLFileExportTest.stl";
	Command command(FileExportLabels::STLFileExportCommandLabel);
	command.setArg(FileExportLabels::IdsLabel, newIds);
	command.setArg(FileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE(command.execute(&world));
}