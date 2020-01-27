#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Command {

class PositionGetCommand : public ICommand
{
public:
	PositionGetCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > parentId;
		Arg< int > childId;
	};

	struct Results : IResults
	{
		Results();

		Result<Math::Vector3dd> position;
	};

	static std::string getName();

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};
	}
}