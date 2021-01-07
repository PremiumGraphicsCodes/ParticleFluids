#pragma once

#include "../../CrystalViewer/Command/ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Command {

class VDBMeshCreateCommand : public ICommand
{
public:
	VDBMeshCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< std::array<int, 3> > triangleIndices;
		Arg< std::array<int, 4> > quadIndices;
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