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
		attributeView("WFAttribute")
	{
		add(&attributeView);
	}

protected:
	void addWireFrame(const std::vector<Math::Vector3dd>& positions);

private:
	WFAttributeView attributeView;
};

	}
}