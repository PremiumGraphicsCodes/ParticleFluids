#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class SceneGetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
	};

	struct Results : IResults
	{
		Results();

		//Result<Math::Vector3dd> center;
		Result<bool> isVisible;
		Result<std::string> name;
		Result<Math::Box3d> boundingBox;

	};

	static std::string getName();

	SceneGetCommand();

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}