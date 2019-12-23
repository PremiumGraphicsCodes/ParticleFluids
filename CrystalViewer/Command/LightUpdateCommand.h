#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class LightUpdateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
		Arg<Math::Vector3dd> position;
		Arg<Graphics::ColorRGBAf> ambient;
		Arg<Graphics::ColorRGBAf> diffuse;
		Arg<Graphics::ColorRGBAf> specular;
		Arg<std::string> name;
	};

	LightUpdateCommand() :
		ICommand(&args, nullptr)
	{}

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
};

	}
}