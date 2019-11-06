#pragma once

#include "../../Crystal/Math/Space3d.h"

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class TrimCommand : public ICommand
{
	struct Args : IArgs
	{
		Args();

		Arg<int> shapeId;
		Arg<Math::Space3d> space;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}