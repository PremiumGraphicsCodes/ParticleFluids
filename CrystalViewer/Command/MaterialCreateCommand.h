#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MaterialCreateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<Graphics::ColorRGBAf> ambient;
		Arg<Graphics::ColorRGBAf> diffuse;
		Arg<Graphics::ColorRGBAf> specular;
		Arg<float> shininess;
		Arg<std::string> textureName;
		Arg<std::string> name;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	MaterialCreateCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}