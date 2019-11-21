#pragma once

#include "ICommand.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../../Crystal/Shape/Vertex.h"
#include "../../Crystal/Shape/Face.h"
#include <vector>

namespace Crystal {
	namespace Command {

class PolygonMeshCreateCommand : public ICommand
{
public:
	PolygonMeshCreateCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< std::vector<Math::Vector3dd> > normals;
		Arg< std::vector<Math::Vector2dd> > texCoords;
		Arg< std::vector<Scene::Vertex > > vertices;
		Arg< std::vector<Scene::Face > > faces;
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