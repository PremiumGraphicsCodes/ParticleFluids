#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"

#include "../../Crystal/Scene/World.h"
#include "../../CrystalViewer/AppBase/Canvas.h"

#include "../../CrystalViewer/AppBase/SpotLightView.h"

#include "../CrystalPhoton/PhotonTracer.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../CrystalPhoton/PhotonCloudScene.h"

namespace Crystal {
	namespace UI {

class PhotonTracerView : public UI::IOkCancelView
{
public:
	PhotonTracerView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onBuild();

	void onStep();

	void onOk();

private:
	SpotLightView lightView;
	Button buildButton;
	Button stepButton;

	Photon::PhotonTracer tracer;
	Scene::ParticleSystemScene* particles;
	Photon::PhotonCloudScene* photonCloud;
};

	}
}