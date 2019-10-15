#pragma once

#include "IArgs.h"
#include "ICommand.h"
#include <filesystem>
#include <vector>

#include "../../Crystal/IO/FileFormat.h"

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

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	bool exportFile(const std::filesystem::path& filePath);

	bool exportFile(const std::filesystem::path& filePath, const IO::FileFormat format);


private:
	Args args;
	Results results;
};

	}
}