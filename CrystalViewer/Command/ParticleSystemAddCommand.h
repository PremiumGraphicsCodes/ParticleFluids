#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
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
		Args();

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< float > pointSize;
		Arg< Graphics::ColorRGBAf > color;
		Arg< std::string > name;
		Arg< bool > isItem;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	static std::string getName();

	void execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};
	}
}