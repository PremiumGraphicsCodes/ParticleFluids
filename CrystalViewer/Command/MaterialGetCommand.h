#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MaterialGetCommand : public ICommand
{
public:
	struct Args : public IArgs
	{
		Args();

		Arg<int> id;
	};

	struct Results : public IResults
	{
		Results();

		Result<Graphics::ColorRGBAf> ambient;
		Result<Graphics::ColorRGBAf> diffuse;
		Result<Graphics::ColorRGBAf> specular;
		Result<float> shininess;
		Result<int> textureId;
		Result<std::string> name;
	};

	MaterialGetCommand() :
		ICommand(&args, nullptr)
	{}

	static std::string getName();

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}