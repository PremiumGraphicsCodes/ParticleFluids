#pragma once

#include "IArgs.h"
#include "ICommand.h"
#include <filesystem>
#include <vector>

#include "../../Crystal/Scene/Scene.h"
#include "../../Crystal/Scene/SceneFactory.h"
#include "../../Crystal/IO/FileFormat.h"

namespace Crystal {
	namespace Command {

class FileImportCommand : public ICommand
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

	FileImportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	bool execute(Scene::World* scene) override;

private:
	bool importFile(const std::filesystem::path& filePath, Scene::World* world);

	bool importFile(const std::filesystem::path& filePath, Scene::World* world, const IO::FileFormat format);

private:
	Args args;
	Results results;
};

	}
}