#include "pch.h"

#include "../VDBCommand/VDBCommandFactory.h"
#include "../VDBCommand/VDBInitCommand.h"
#include "../VDBCommand/VDBFileReadCommand.h"
#include "../VDBCommand/VDBFileWriteCommand.h"

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
/*

VDBFileReadCommand fileReadCommand;
VDBPSToVolumeCommand psToVolumecommand;
VDBFileWriteCommand fileWriteCommand;
JSONFileWriter writer;
writer.add(&fileReadCommand);
writer.add(&psToVolumecommand);
writer.add(&fileWriteCommand);

writer.write("./TestFiles/test02.json");
*/
