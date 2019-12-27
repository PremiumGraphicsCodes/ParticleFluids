#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Command {

class GetMatrixCommand : public ICommand
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

		Arg<Math::Matrix4dd> matrix;
	};

	static std::string getName();

	GetMatrixCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}