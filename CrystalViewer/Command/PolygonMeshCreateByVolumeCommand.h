#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/IVolume3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class PolygonMeshCreateByVolumeCommand : public ICommand
{
public:
	PolygonMeshCreateByVolumeCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::shared_ptr<Math::IVolume3d> > volume;
		Arg< int > uDivNum;
		Arg< int > vDivNum;
		Arg< int > wDivNum;
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