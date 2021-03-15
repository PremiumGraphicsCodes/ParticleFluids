#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"

#include "../../Crystal/Scene/World.h"
#include "../../CrystalViewer/AppBase/Canvas.h"

namespace Crystal {
	namespace UI {

class PhotonTracerView : public UI::IOkCancelView
{
public:
	PhotonTracerView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk();

private:
	//Sphere3dView sphereView;
	//DoubleView divideLengthView;
};

	}
}