#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Command {

class ScaleCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args() :
			id("Id", -1),
			ratio("Ratio", Math::Vector3dd())
		{
			add(&id);
			add(&ratio);
		}

		Arg<int> id;
		Arg<Math::Vector3dd> ratio;
	};

	ScaleCommand() :
		ICommand(&args)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
};

	}
}