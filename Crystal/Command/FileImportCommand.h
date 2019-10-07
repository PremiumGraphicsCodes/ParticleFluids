#pragma once

#include "IArgs.h"
#include "ICommand.h"
#include <filesystem>
#include <vector>

namespace Crystal {
	namespace Command {

class FileImportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results();

		Result< bool > isOk;
	};

	FileImportCommand() :
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