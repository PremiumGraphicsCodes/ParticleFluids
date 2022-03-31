#include "pch.h"

#include "CrystalVDB/VDBCommand/VDBCommandFactory.h"
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/ToVDBVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBMeshToVolumeCommand.h"
#include "CrystalVDB/VDBCommand/VDBSTLFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBSTLFileWriteCommand.h"

using namespace Crystal::VDB;

TEST(VDBCommandFactoryTest, TestCreate)
{
	VDBCommandFactory factory;
	EXPECT_FALSE( factory.createCommand(VDBInitCommand::getName()) == nullptr);
	EXPECT_FALSE( factory.createCommand(ToVDBVolumeCommand::getName()) == nullptr);
	EXPECT_FALSE( factory.createCommand(VDBMeshToVolumeCommand::getName()) == nullptr);
	factory.createCommand(VDBSTLFileReadCommand::getName());
	factory.createCommand(VDBSTLFileWriteCommand::getName());
}