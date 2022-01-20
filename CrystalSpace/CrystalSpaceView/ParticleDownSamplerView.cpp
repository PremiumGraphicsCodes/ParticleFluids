#include "ParticleDownSamplerView.h"

#include "Crystal/Math/Sphere3d.h"
#include "Crystal/Graphics/ColorRGBA.h"

#include "Crystal/Shape/ParticleSystem.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "../CrystalSpace/ParticleDownSampler.h"

#include <random>
#include <memory>
using namespace Crystal::Shape;

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

ParticleDownSamplerView::ParticleDownSamplerView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas)
{
}

void ParticleDownSamplerView::onOk()
{
	const Sphere3df sphere(Vector3df(0,0,0), 10.0f);
	const auto bb = sphere.getBoundingBox();

	ParticleSystem<float> ps;
	const auto& length = bb.getLength();
	const auto divLength = 1.0;
	const auto du = divLength / length.x;
	const auto dv = divLength / length.y;
	const auto dw = divLength / length.z;
	const auto tolerance = 1.0e-12;
	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
			for (auto w = 0.0; w < 1.0 + tolerance; w += dw) {
				const auto p = bb.getPosition(u, v, w);
				if (sphere.isInside(p)) {
					ps.add(p, 0.0f);
				}
			}
		}
	}

	const auto newPoints = ParticleDownSampler::downSample(ps.getIParticles(), 2.0f);

	ParticleAttribute attr;
	attr.color = ColorRGBAf(1, 1, 1, 1);
	attr.size = 1.0f;
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(newPoints, attr);
	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), name, std::move(shape));
	getWorld()->getScenes()->addScene(scene);
	const auto newId = scene->getId();

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());

}