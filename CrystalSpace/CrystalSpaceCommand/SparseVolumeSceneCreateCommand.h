#pragma once

#include "../../CrystalViewer/Command/ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Command {

class SparseVolumeSceneCreateCommand : public ICommand
{
public:
	SparseVolumeSceneCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::array<int,3> > resolutions;
		Arg< Math::Box3d > boundingBox;
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