#pragma once

#include "ICommand.h"
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"
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
		Args() :
			lines("Lines", {}),
			lineWidth("LineWidth", 1.0f),
			color("Color", Graphics::ColorRGBAf(1, 1, 1, 1)),
			name("Name", std::string("")),
			isItem("IsItem", false)
		{
			add(&lines);
			add(&lineWidth);
			add(&color);
			add(&name);
			add(&isItem);
		}

		Arg< std::vector<Math::Line3dd> > lines;
		Arg< float > lineWidth;
		Arg< Graphics::ColorRGBAf > color;
		Arg< std::string > name;
		Arg< bool > isItem;
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