#pragma once

#include "../../CrystalViewer/AppBase/IView.h"

#include "../../CrystalViewer/AppBase/Sphere3dView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

#include "../../Crystal/Scene/World.h"
#include "../../CrystalViewer/AppBase/Canvas.h"

namespace Crystal {
	namespace UI {

class PCSphereView : public UI::IView
{
public:
	PCSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk();

private:
	Sphere3dView sphereView;
	DoubleView divideLengthView;
};

	}
}