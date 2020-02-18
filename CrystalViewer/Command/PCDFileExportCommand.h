#pragma once

#include "ICommand.h"
//#include <filesystem>

namespace Crystal {
	namespace Command {

class PCDFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::vector<int> > ids;
		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();
	};

	PCDFileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}