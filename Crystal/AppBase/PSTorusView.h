#pragma once

#include "IOkCancelView.h"

#include "Torus3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSTorusView : public IOkCancelView
{
public:
	PSTorusView(Scene::World* model, Canvas* canvas);

protected:
	void onShow() override;

	void onOk() override;

private:
	TorusView torusView;
	PSAttributeView attribute;
	IntView count;
};

	}
}