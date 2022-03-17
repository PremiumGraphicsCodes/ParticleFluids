// VDBRunner.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include "CrystalVDB/VDBCommand/VDBCommandFactory.h"
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileReadCommand.h"
#include "CrystalVDB/VDBCommand/VDBFileWriteCommand.h"
#include "CrystalScene/Command/JSONFileWriter.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::Command;
using namespace Crystal::VDB;

int main()
{
	Crystal::Scene::World world;

	VDBInitCommand initCommand;
	initCommand.execute(&world);

	VDBCommandFactory factory;
	/*
	VDBInitCommand command;
	VDBFileReadCommand fileReadCommand;
	VDBFileWriteCommand fileWriteCommand;
	JSONFileWriter writer;
	writer.add(&fileReadCommand);
	writer.add(&fileWriteCommand);
	writer.write("./TestFiles/test02.json");
	*/
	JSONFileReader reader;
	reader.read("./TestFiles/test01.json", factory);
	auto commands = reader.getCommands();
	for (auto& c : commands) {
		std::cout << "Start " << c->getCommandName() << std::endl;
		c->execute(&world);
		std::cout << "End " << c->getCommandName() << std::endl;
	}
	//auto json = converter.toJSON(command);

	//std::ofstream o("pretty.json");
	//o << std::setw(4) << j << std::endl;
	//factory.createCommand()
}

