#pragma once

#include "IArgs.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraRotateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< float > rx;
		Arg< float > ry;
		Arg< float > rz;
	};

	CameraRotateCommand() :
		ICommand(&args)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	Args args;
};

	}
}