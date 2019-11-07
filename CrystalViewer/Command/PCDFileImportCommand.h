#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class PCDFileImportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();

		Result< bool > isOk;
	};

	PCDFileImportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}