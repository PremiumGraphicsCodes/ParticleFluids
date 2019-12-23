#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MaterialUpdateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
		Arg<Graphics::ColorRGBAf> ambient;
		Arg<Graphics::ColorRGBAf> diffuse;
		Arg<Graphics::ColorRGBAf> specular;
		Arg<float> shininess;
		Arg<int> textureId;
		Arg<std::string> name;
	};

	MaterialUpdateCommand() :
		ICommand(&args, nullptr)
	{}

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
};

	}
}