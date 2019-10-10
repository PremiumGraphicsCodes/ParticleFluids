#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class ParticleSystemAddCommand : public ICommand
{
public:
	ParticleSystemAddCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args() :
			positions("Positions", {}),
			pointSize("PointSize", 1.0f),
			color("Color", Graphics::ColorRGBAf(1,1,1,1)),
			name("Name", std::string("")),
			isItem("IsItem", false)
		{
			add(&positions);
			add(&pointSize);
			add(&color);
			add(&name);
			add(&isItem);
		}

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< float > pointSize;
		Arg< Graphics::ColorRGBAf > color;
		Arg< std::string > name;
		Arg< bool > isItem;
	};

	struct Results : IResults
	{
		Results() :
			newId("NewId", -1)
		{
			add(&newId);
		}

		Result<int> newId;
	};

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};
	}
}