#include "pch.h"

#include "../Command/Command.h"
#include "../Command/Public/OBJFileExportLabels.h"

#include "../../Crystal/Math/Quad3d.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(OBJFileExportCommand, TestExecute)
{
	World world;

	Quad3d quad(Vector3dd(0,0,0), Vector3dd(1,0,0), Vector3dd(0,1,0));
	PolygonMeshBuilder builder;
	builder.add(quad);
	auto scene = new PolygonMeshScene(1, "", builder.build());
	world.getScenes()->addScene(scene);

	const std::vector<int> ids = { scene->getId() };
	const std::string filePath = "./OBJFileExportTest.obj";
	Command command(OBJFileExportLabels::CommandNameLabel);
	command.setArg(OBJFileExportLabels::IdsLabel, ids);
	command.setArg(OBJFileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE(command.execute(&world));
}