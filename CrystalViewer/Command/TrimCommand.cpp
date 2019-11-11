#include "TrimCommand.h"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/IShapeScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "Public/TrimLabels.h"
#include "../../Crystal/Math/Sphere3d.h"


using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TrimCommand::Args::Args() :
	shapeId(TrimLabels::ShapeIdLabel, -1),
	spheres("Spheres", std::vector<Sphere3d>())
//	space(::SpaceLabel, Math::Space3d())
{
	add(&shapeId);
	add(&spheres);
};

TrimCommand::Results::Results() :
	newId(TrimLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string TrimCommand::getName()
{
	return TrimLabels::TrimCommandLabel;
}

void TrimCommand::execute(World* world)
{
	auto shape = world->getObjects()->findSceneById<IShapeScene*>(args.shapeId.getValue());
	Space3d space;
	auto spheres = args.spheres.getValue();
	for (auto& s : spheres) {
		space.add(&s);
	}
	if (shape->getType() == SceneType::ParticleSystemScene) {
		auto pss = static_cast<ParticleSystemScene*>(shape);
		auto ps = pss->getShape();
		const auto& particles = ps->getParticles();
		std::vector<Vector3dd> positions;
		for (auto p : particles) {
			const auto& pos = p->getPosition();
			if (space.isInside(pos)) {
				positions.push_back(pos);
			}
		}
		ParticleAttribute attr;
		attr.color = Crystal::Graphics::ColorRGBAf(1.0, 0.0, 0.0, 0.0);
		attr.size = 1.0f;
		auto newObj = world->getObjectFactory()->createParticleSystemScene(positions, attr, "Trimmed");
		world->getObjects()->addScene(newObj);
		results.newId.setValue(newObj->getId());
	}
}
