#pragma once

#include "IArgs.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraSetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< Math::Vector3dd > eyePosition;
	};

	CameraSetCommand() :
		ICommand(&args)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	Args args;
};

	}
}