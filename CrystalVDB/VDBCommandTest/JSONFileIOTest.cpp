#include "pch.h"

#include "../VDBCommand/VDBCommandFactory.h"
#include "../VDBCommand/VDBInitCommand.h"
#include "../VDBCommand/VDBFileReadCommand.h"
#include "../VDBCommand/VDBFileWriteCommand.h"
#include "../VDBCommand/VDBPSToVolumeCommand.h"
#include "../VDBCommand/VDBSceneCreateCommand.h"
#include "../VDBCommand/VDBSTLFileReadCommand.h"
#include "../VDBCommand/VDBSTLFileWriteCommand.h"
#include "../VDBCommand/VDBVolumeToMeshCommand.h"
#include "../VDBCommand/VDBMeshToVolumeCommand.h"
#include "../VDBCommand/VDBFilterCommand.h"
#include "../VDBCommand/VDBCompositeCommand.h"
#include "../VDBCommand/VDBResamplingCommand.h"

#include "../VDBCommand/VDBSceneFileReadCommand.h"
#include "../VDBCommand/VDBSceneFileWriteCommand.h"
#include "../VDBCommand/VDBSceneFilterCommand.h"

#include "CrystalScene/Command/JSONFileWriter.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::VDB;
using namespace Crystal::Command;

TEST(VDBRunnerTest, TestInitCommand)
{
	const std::string filepath("./TestFiles/init.json");

	VDBInitCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE( writer.write(filepath) );

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE( reader.read(filepath, factory) );
}

TEST(VDBRunnerTest, TestFileReadCommand)
{
	const std::string filepath("./TestFiles/read.json");

	VDBFileReadCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE( writer.write(filepath) );

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE( reader.read(filepath, factory) );
}

TEST(VDBRunnerTest, TestFileWriteCommand)
{
	const std::string filepath("./TestFiles/write.json");

	VDBFileWriteCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE( writer.write(filepath) );

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE( reader.read(filepath, factory) );
}

TEST(VDBRunnerTest, TestPSToVolumeCommand)
{
	const std::string filepath("./TestFiles/ps_to_volume.json");

	VDBPSToVolumeCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestPointsSceneCreateCommand)
{
	const std::string filepath("./TestFiles/vdb_scene_create_points.json");

	VDBSceneCreateCommand command;
	VDBSceneCreateCommand::Args args;
	args.sceneType.setValue(std::string("VDBPoints"));
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestReadSTLCommand)
{
	const std::string filepath("./TestFiles/read_stl.json");

	VDBSTLFileReadCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestWriteSTLCommand)
{
	const std::string filepath("./TestFiles/write_stl.json");

	VDBSTLFileWriteCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestVolumeToMeshCommand)
{
	const std::string filepath("./TestFiles/volume_to_mesh.json");

	VDBVolumeToMeshCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestMeshToVolumeCommand)
{
	const std::string filepath("./TestFiles/mesh_to_volume.json");

	VDBMeshToVolumeCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestFilterCommand)
{
	const std::string filepath("./TestFiles/filter.json");

	VDBFilterCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestCompositeCommand)
{
	const std::string filepath("./TestFiles/composite_union.json");
	VDBCompositeCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestResamplingCommand)
{
	const std::string filepath = "./TestFiles/resampling_box.json";
	VDBResamplingCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneFileWriteCommand)
{
	const std::string filepath = "./TestFiles/scene_write.json";
	VDBSceneFileWriteCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneFileReadCommand)
{
	const std::string filepath = "./TestFiles/scene_read.json";
	VDBSceneFileReadCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneFilterCommand)
{
	const std::string filepath = "./TestFiles/scene_filter.json";
	VDBSceneFilterCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}