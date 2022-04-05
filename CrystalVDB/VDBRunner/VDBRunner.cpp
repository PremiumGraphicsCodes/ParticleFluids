// VDBRunner.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include "CrystalVDB/VDBCommand/VDBCommandFactory.h"
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileWriteCommand.h"
#include "CrystalVDB/VDBCommand/VDBPSToVolumeCommand.h"
#include "CrystalScene/Command/JSONFileWriter.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::Command;
using namespace Crystal::VDB;

void testDump()
{
	JSONFileWriter writer;
}

int main()
{
	Crystal::Scene::World world;

	VDBInitCommand initCommand;
	initCommand.execute(&world);

	VDBCommandFactory factory;
	JSONFileReader reader;
	reader.read("./TestFiles/test_resampling.json", factory);
	auto commands = reader.getCommands();
	for (auto& c : commands) {
		std::cout << "Start " << c->getCommandName() << std::endl;
		const auto isOk = c->execute(&world);
		if (!isOk) {
			std::cout << "Failed" << std::endl;
		}
		std::cout << "End " << c->getCommandName() << std::endl;
	}
}

