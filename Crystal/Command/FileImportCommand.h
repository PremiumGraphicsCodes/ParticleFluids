#pragma once

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
		std::filesystem::path filePath;
	};

	struct Results : IResults
	{

	};

	FileImportCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::Scene* scene) override {}

private:
	Args args;
	Results results;
};

	}
}