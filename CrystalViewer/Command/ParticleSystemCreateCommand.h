#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class ParticleSystemCreateCommand : public ICommand
{
public:
	ParticleSystemCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< float > pointSize;
		Arg< Graphics::ColorRGBAf > color;
		Arg< std::string > name;
		Arg< int > layer;
		Arg< Math::Matrix4dd > matrix;
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};
	}
}