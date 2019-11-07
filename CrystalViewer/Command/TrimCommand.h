
#pragma once

#include "../../Crystal/Math/Space3d.h"
//#include "../../Crystal/Math/Sphere3d.h"

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class TrimCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> shapeId;
		//Arg<Math::Space3d> space;
		Arg<std::vector<Math::Sphere3d>> spheres;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	TrimCommand() :
		ICommand(&args, &results)
	{
	}

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}