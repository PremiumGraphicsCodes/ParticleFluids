#pragma once

#include "IOkCancelView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class IWFAddView : public IOkCancelView
{
public:
	IWFAddView(const std::string& name, Scene::World* model, Canvas* canvas) :
		IOkCancelView(name, model, canvas),
		attributeView("WFAttribute"),
		nameView("Name", "WireFrame01")
	{
		add(&attributeView);
		add(&nameView);
	}

protected:
	void addWireFrame(const std::vector<Math::Line3dd>& lines);

private:
	WFAttributeView attributeView;
	StringView nameView;
};

	}
}