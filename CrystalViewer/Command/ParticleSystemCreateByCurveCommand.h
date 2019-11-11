#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/ICurve3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class ParticleSystemCreateByCurveCommand : public ICommand
{
public:
	ParticleSystemCreateByCurveCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<std::unique_ptr<Math::ICurve3d>> > curves;
		Arg< int > uCount;

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