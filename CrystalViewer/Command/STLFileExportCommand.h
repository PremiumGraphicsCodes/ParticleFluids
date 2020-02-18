#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class STLFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::vector<int> > ids;
		Arg< bool > isBinary;
		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results();

//		Result< bool > isOk;
	};

	STLFileExportCommand() :
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