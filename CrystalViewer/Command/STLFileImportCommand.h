#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class STLFileImportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< bool > isBinary;
		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();

		Result< bool > isOk;
	};

	STLFileImportCommand() :
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