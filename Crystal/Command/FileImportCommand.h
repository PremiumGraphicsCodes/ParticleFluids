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
		Args() :
			filePath("FilePath", "")
		{}

		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results() :
			isOk("IsOk", false)
		{}

		Arg< bool > isOk;
	};

	FileImportCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}