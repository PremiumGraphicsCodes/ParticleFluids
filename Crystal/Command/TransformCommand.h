#pragma once

#include "ICommand.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Command {

class TransformCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args() :
			id("Id", -1),
			matrix("Matrix", Math::Matrix4dd())
		{
			add(&id);
			add(&matrix);
		}

		Arg<int> id;
		Arg<Math::Matrix4dd> matrix;
	};

	struct Results : IResults
	{
		Results()
		{
		}
	};

	TransformCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};
	}
}