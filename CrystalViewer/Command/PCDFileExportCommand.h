#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class PCDFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< int > id;
		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results();

		Result< bool > isOk;
	};

	PCDFileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
private:
	Args args;
	Results results;
};

	}
}