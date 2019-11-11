#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/ISurface3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class PolygonMeshCreateBySurfaceCommand : public ICommand
{
public:
	PolygonMeshCreateBySurfaceCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::ISurface3d*> > surfaces;
		Arg< int > uDivNum;
		Arg< int > vDivNum;
		Arg< std::string > name;
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