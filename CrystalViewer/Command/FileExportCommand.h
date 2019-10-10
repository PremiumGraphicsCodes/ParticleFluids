#pragma once

#include "IArgs.h"
#include "ICommand.h"
#include <filesystem>
#include <vector>

namespace Crystal {
	namespace Command {

class FileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args() :
			filePath("FilePath", "")
		{
			add(&filePath);
		}

		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results() :
			isOk("IsOk", false)
		{
			add(&isOk);
		}

		Result< bool > isOk;
	};

	FileExportCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}