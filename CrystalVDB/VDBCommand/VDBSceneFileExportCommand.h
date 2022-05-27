#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {
		class VDBParticleSystemScene;
		class VDBPolygonMeshScene;

class VDBSceneFileExportCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
		Command::Arg<std::string> fileFormat;
		Command::Arg<int> vdbSceneId;
	};

	struct Results : Command::IResults
	{
		Results();

		//Command::Result<std::vector<int>> newIds;
	};

	VDBSceneFileExportCommand();

	explicit VDBSceneFileExportCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;

	bool writePLY(VDBParticleSystemScene* vdbPoints);

	bool writePCD(VDBParticleSystemScene* vdbPoints);

	bool writeSTL(VDBPolygonMeshScene* mesh);

	bool writeOBJ(VDBPolygonMeshScene* mesh);
};

	}
}