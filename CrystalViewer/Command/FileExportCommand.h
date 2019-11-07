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
		Args();

		Arg< int > id;
		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();

		Result< bool > isOk;
	};

	FileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	void exportFile(const std::filesystem::path& filePath, const IO::FileFormat format, Scene::World* world);


private:
	Args args;
	Results results;
};

	}
}