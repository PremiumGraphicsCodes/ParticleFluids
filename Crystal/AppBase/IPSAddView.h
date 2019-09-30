#pragma once

#include "IOkCancelView.h"
#include "PSAttributeView.h"

namespace Crystal {
	namespace UI {

class IPSAddView : public IOkCancelView
{
public:
	IPSAddView(const std::string& name, Scene::World* model, Canvas* canvas) : 
		IOkCancelView(name, model, canvas),
		attributeView("PSAttribute")
	{
		add(&attributeView);
	}

protected:
	void addParticleSystem(const std::vector<Math::Vector3dd>& positions);

private:
	PSAttributeView attributeView;
};

	}
}