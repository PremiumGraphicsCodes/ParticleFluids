#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
//#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class ISolidAddView : public IOkCancelView
{
public:
	ISolidAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addSolid(const std::vector<Math::Vector3dd>& positions, const std::vector<Shape::WireFrameEdge>& edges);

private:
	//WFAttributeView attributeView;
	StringView nameView;
};

	}
}