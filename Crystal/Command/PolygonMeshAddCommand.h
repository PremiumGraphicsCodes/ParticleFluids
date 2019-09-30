#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"
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
			//pointSize("PointSize", 1.0f),
			//color("Color", Graphics::ColorRGBAf(1, 1, 1, 1)),
			name("Name", std::string(""))
		{
			add(&positions);
			add(&normals);
			//add(&pointSize);
			//add(&color);
			add(&name);
		}

		Arg< std::vector<Math::Vector3dd> > positions;
		Arg< std::vector<Math::Vector3dd> > normals;
		Arg< std::vector<Math::Vector2dd> > texCoords;
		//Arg< Graphics::ColorRGBAf > color;
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