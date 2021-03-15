#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"

#include "../../Crystal/Scene/World.h"
#include "../../CrystalViewer/AppBase/Canvas.h"

#include "../../CrystalViewer/AppBase/SpotLightView.h"

#include "../CrystalPhoton/PhotonTracer.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace UI {

class PhotonTracerView : public UI::IOkCancelView
{
public:
	PhotonTracerView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onBuild();

	void onOk();

private:
	SpotLightView lightView;
	Button buildButton;
	//Sphere3dView sphereView;
	//DoubleView divideLengthView;
	Photon::PhotonTracer tracer;
	Scene::ParticleSystemScene* particles;
};

	}
}