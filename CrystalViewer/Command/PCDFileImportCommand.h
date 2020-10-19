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

		Result<int> newId;
		//Result< int > newId;
	};

	PCDFileImportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}