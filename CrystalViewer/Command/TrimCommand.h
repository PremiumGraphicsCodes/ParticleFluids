#pragma once

#include "../../Crystal/Math/Space3d.h"

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class TrimCommand : public ICommand
{
	struct Args : IArgs
	{
		Arg<int> shapeId;
		Arg<Math::Space3d> space;
	};

	struct Results : IResults
	{
		Result<int> newId;
	};

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}