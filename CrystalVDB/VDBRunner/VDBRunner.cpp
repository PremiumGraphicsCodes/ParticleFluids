// VDBRunner.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include "CrystalVDB/VDBCommand/VDBCommandFactory.h"
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::Command;
using namespace Crystal::VDB;

int main()
{
	VDBCommandFactory factory;
	JSONFileReader reader;
	//reader.read("./TestFiles/test01.json", factory);
	//auto json = converter.toJSON(command);

	//std::ofstream o("pretty.json");
	//o << std::setw(4) << j << std::endl;
	//factory.createCommand()
}

