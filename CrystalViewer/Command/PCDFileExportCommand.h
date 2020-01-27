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

		Arg< int > id;
		Arg< std::string > filePath;
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

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}