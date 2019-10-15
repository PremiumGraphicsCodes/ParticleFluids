#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class PCDFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< bool > isBinary;
		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results();

		Result< bool > isOk;
	};

	PCDFileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	void exportAscii(Scene::World* world);

	void exportBinary(Scene::World* world);

private:
	Args args;
	Results results;
};

	}
}