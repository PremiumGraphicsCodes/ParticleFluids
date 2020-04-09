#include "pch.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/ParticleAttribute.h"

#include "../../Crystal/Math/Quad3d.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../Command/Command.h"
#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(FileExportCommand, TestExportPCD)
{
	World world;

	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>();
	shape->add(Vector3dd(0, 0, 0), ParticleAttribute());
	auto ps = new ParticleSystemScene(1,"", std::move(shape));
	world.getObjects()->addScene(ps);

	const std::string filePath = "TestFileExport.pcd";
	Crystal::Command::Command command(::FileExportLabels::FileExportCommandLabel);
	command.setArg(::FileExportLabels::FilePathLabel, filePath);
	const auto isOk = command.execute(&world);
	EXPECT_TRUE(isOk);
}

TEST(FileExportCommand, TestExportOBJ)
{
	World world;

	Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));
	PolygonMeshBuilder builder;
	builder.add(quad);
	auto scene = new PolygonMeshScene(1, "", builder.build());
	world.getObjects()->addScene(scene);

	const std::string filePath = "TestFileExport.obj";
	Crystal::Command::Command command(::FileExportLabels::FileExportCommandLabel);
	command.setArg(::FileExportLabels::FilePathLabel, filePath);
	const auto isOk = command.execute(&world);
	EXPECT_TRUE(isOk);

}
