#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraGetCommand : public ICommand
{
public:
	struct Results : IResults
	{
		Results();

		Result< double > near;
		Result< double > far;
		Result< Math::Vector3dd > eyePosition;
		Result< Math::Vector3dd > targetPosition;
	};

	CameraGetCommand() :
		ICommand(nullptr, &results)
	{}

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	Results results;
};

	}
}