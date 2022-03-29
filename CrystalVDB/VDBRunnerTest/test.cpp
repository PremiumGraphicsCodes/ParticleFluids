#include "pch.h"

#include "../VDBCommand/VDBCommandFactory.h"
#include "../VDBCommand/VDBInitCommand.h"
#include "../VDBCommand/VDBFileReadCommand.h"

#include "CrystalScene/Command/JSONFileWriter.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::VDB;
using namespace Crystal::Command;

TEST(VDBRunnerTest, TestInitCommand)
{
	VDBInitCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	writer.write("./TestFiles/init.json");
}

TEST(VDBRunnerTest, TestFileReadCommand)
{
	VDBFileReadCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	writer.write("./TestFiles/read.json");

	VDBCommandFactory factory;
	JSONFileReader reader;
	reader.read("./TestFiles/read.json", factory);
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
