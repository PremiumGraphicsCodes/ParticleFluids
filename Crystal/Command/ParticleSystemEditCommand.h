#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class ParticleSystemEditCommand : public ICommand
{
public:
	ParticleSystemEditCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args() :
			pointSize("PointSize", 1.0f),
			color("Color", Graphics::ColorRGBAf(1, 1, 1, 1)),
			name("Name", std::string(""))
		{
			add(&pointSize);
			add(&color);
			add(&name);
		}

		Arg< float > pointSize;
		Arg< Graphics::ColorRGBAf > color;
		Arg< std::string > name;
	};

	struct Results : IResults
	{
	};

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};
	}
}