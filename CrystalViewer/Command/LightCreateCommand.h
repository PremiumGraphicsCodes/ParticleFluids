#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class LightCreateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<Math::Vector3dd> position;
		Arg<Graphics::ColorRGBAf> ambient;
		Arg<Graphics::ColorRGBAf> diffuse;
		Arg<Graphics::ColorRGBAf> specular;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	LightCreateCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}