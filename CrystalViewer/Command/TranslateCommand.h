#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Command {

class TranslateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args() :
			id("Id", -1),
			vector("Vector", Math::Vector3dd())
		{
			add(&id);
			add(&vector);
		}

		Arg<int> id;
		Arg<Math::Vector3dd> vector;
	};

	static std::string getName();

	TranslateCommand() :
		ICommand(&args)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
};
	}
}