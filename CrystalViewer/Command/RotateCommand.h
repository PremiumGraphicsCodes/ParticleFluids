#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Command {

class RotateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args() :
			id("Id", -1),
			matrix("Matrix", Math::Matrix3dd())
		{
			add(&id);
			add(&matrix);
		}

		Arg<int> id;
		Arg<Math::Matrix3dd> matrix;
	};

	static std::string getName();

	RotateCommand() :
		ICommand(&args)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
};

	}
}