#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

#include "CrystalScene/Scene/World.h"
#include "CrystalScene/AppBase/Canvas.h"

#include "CrystalScene/AppBase/SpotLightView.h"

#include "../CrystalPhoton/PhotonTracer.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "../CrystalPhoton/PhotonCloudScene.h"

namespace Crystal {
	namespace UI {

class MovingPhotonView : public UI::IOkCancelView
{
public:
	MovingPhotonView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onAddVolume();

	void onStep();

	void onOk();

private:
	SpotLightView lightView;
	Button addVolumeButton;
	Button stepButton;

	Photon::PhotonTracer tracer;
	Scene::ParticleSystemScene* particles;
	Photon::PhotonCloudScene* photonCloud;
};

	}
}