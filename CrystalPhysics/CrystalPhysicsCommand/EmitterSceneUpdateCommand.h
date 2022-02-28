#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class EmitterSceneUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<int> particleSystemId;
		Command::Arg<float> particleRadius;
		Command::Arg<float> density;
		Command::Arg<float> stiffness;
		Command::Arg<float> viscosity;
		Command::Arg<Math::Vector3df> initialVelocity;
		Command::Arg<std::string> name;

		Command::Arg<int> startStep;
		Command::Arg<int> endStep;
		Command::Arg<int> interval;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	EmitterSceneUpdateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}