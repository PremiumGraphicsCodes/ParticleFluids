#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class OBJFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::vector<int> > ids;
		Arg< std::filesystem::path > filePath;
	};

	struct Results : IResults
	{
		Results();

		//Result< bool > isOk;
	};

	OBJFileExportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	bool execute(Scene::World* scene) override;

private:
	bool exportOBJ(const std::filesystem::path& filePath, Scene::PolygonMeshScene& polygon);

	bool exportMTL(const std::filesystem::path& filePath, Scene::PolygonMeshScene& appearances);

private:
	Args args;
	Results results;
};

	}
}