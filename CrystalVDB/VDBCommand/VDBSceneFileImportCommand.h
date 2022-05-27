#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneFileReadCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
		Command::Arg<std::string> fileFormat;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result<int> newSceneId;

		//Command::Result<std::vector<int>> newIds;
	};

	VDBSceneFileReadCommand();

	explicit VDBSceneFileReadCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;

	bool readPoints(Scene::World* world);

	bool readVolume(Scene::World* world);
};

	}
}