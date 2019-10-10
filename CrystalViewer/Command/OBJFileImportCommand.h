#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class OBJFileImportCommand : public ICommand
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

	OBJFileImportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	bool importOBJ(const std::filesystem::path& filePath, Scene::World* world);

	bool importMTL(const std::filesystem::path& filePath, Scene::World* world);

	bool importOBJWithMTL(const std::filesystem::path& filePath, Scene::World* world);

private:
	Args args;
	Results results;
};

	}
}