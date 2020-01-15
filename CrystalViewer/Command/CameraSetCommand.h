#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraSetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< double > near;
		Arg< double > far;
		Arg< Math::Vector3dd > eyePosition;
		Arg< Math::Vector3dd > targetPosition;
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