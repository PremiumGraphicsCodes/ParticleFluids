#include "VDBParticleSystemView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../VDBConverter/VDBParticleSystem.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemView::VDBParticleSystemView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	sphereView("Sphere"),
	divideLengthView("DivideLength", 0.1)
{
	add(&sphereView);
	add(&divideLengthView);
}

void VDBParticleSystemView::onOk()
{
	const auto& sphere = sphereView.getValue();
	const auto bb = sphere.getBoundingBox();

	std::vector<Vector3dd> positions;
	const auto& length = bb.getLength();
	const auto divLength = divideLengthView.getValue();
	const auto du = divLength / length.x;
	const auto dv = divLength / length.y;
	const auto dw = divLength / length.z;
	const auto tolerance = 1.0e-12;
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
			for (auto w = 0.0; w < 1.0 + tolerance; w += dw) {
				const auto p = bb.getPosition(u, v, w);
				if (sphere.isInside(p)) {
					positions.push_back(p);
				}
			}
		}
	}
	VDBParticleSystem vdb;
	for (auto p : positions) {
		vdb.add(p, 1.0f);
	}
	auto ps = vdb.toCrystal();
	ParticleAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 1, 1, 1);
	attr.size = 1.0f;
	auto newShape = std::make_unique<Crystal::Shape::ParticleSystem<Crystal::Scene::ParticleAttribute>>(ps->getPositions(), attr);
	ParticleSystemScene* newScene = new ParticleSystemScene(getWorld()->getNextSceneId(), "VDBPS",std::move(newShape));
	newScene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(newScene);
}
