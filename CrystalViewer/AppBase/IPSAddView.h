#pragma once

#include "IOkCancelView.h"
#include "PSAttributeView.h"
#include "Matrix4dView.h"
#include "ComboBox.h"

namespace Crystal {
	namespace UI {

class IPSAddView : public IOkCancelView
{
public:
	IPSAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addParticleSystem(const std::vector<Math::Vector3dd>& positions);

private:
	//Matrix4dView matrixView;
	PSAttributeView attributeView;
	ComboBox presenterView;
};

	}
}