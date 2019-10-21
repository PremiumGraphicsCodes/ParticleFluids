#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class WireFrameAddCommand : public ICommand
{
public:
	WireFrameAddCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::Line3dd> > lines;
		Arg< float > lineWidth;
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