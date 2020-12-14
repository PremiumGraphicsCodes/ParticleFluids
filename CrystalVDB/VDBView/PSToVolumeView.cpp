#include "PSToVolumeView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../VDBConverter/ParticleSystemToVolumeConverter.h"
#include "../VDBConverter/VolumeToMeshConverter.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

PSToVolumeView::PSToVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas)
{
	add(&particleSystemSelectView);
}

void PSToVolumeView::onOk()
{
	auto id = particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}

	VDBParticleSystem ps;
	auto particles = scene->getShape()->getParticles();
	for (auto p : scene->getShape()->getParticles()) {
		ps.add(p->getPosition(), p->getAttribute().size);

	}

	ParticleSystemToVolumeConverter converter;
	auto volume = converter.toVolume(ps, 5.0f);

	VolumeToMeshConverter toMeshConverter;
	auto mesh = toMeshConverter.toMesh(*volume);

	auto newMesh = mesh->toCrystal();
	auto newScene = new Crystal::Scene::PolygonMeshScene(getWorld()->getNextSceneId(), "Mesh", std::move(newMesh));

	auto group = new FaceGroupScene(getWorld()->getNextSceneId(), "FaceGroup", newScene);
	newScene->addGroup(group);
	const auto& faces = newScene->getShape()->faces;
	for (auto f : faces) {
		group->addFace(f);
	}

	newScene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(newScene);
}

