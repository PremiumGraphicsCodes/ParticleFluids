#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"
#include "../Scene/Vertex.h"
#include "../Scene/Face.h"
#include <vector>

namespace Crystal {
	namespace Command {

class PolygonMeshAddCommand : public ICommand
{
public:
	PolygonMeshAddCommand() :
		ICommand(&args, &results)
	{}

	struct Args : IArgs
	{
		Args() :
			positions("Positions", {}),
			normals("Normals", {}),
			texCoords("TexCoords", {}),
			vertices("Vertices", {}),
			faces("Faces", {}),
			name("Name", std::string(""))
		{
			add(&positions);
			add(&normals);
			add(&texCoords);
			add(&vertices);
			add(&faces);
			add(&name);
		}

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< std::vector<Math::Vector3dd> > normals;
		Arg< std::vector<Math::Vector2dd> > texCoords;
		Arg< std::vector<Scene::Vertex > > vertices;
		Arg< std::vector<Scene::Face > > faces;
		Arg< std::string > name;
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