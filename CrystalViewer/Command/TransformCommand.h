#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Command {

class TransformCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
		Arg<Math::Matrix4dd> matrix;
	};

	static std::string getName();

	TransformCommand() :
		ICommand(&args)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
};
	}
}