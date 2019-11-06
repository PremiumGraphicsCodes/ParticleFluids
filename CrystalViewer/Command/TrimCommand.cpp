#include "TrimCommand.h"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/IShapeScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "Public/TrimLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TrimCommand::Args::Args() :
	shapeId(::ShapeIdLabel, -1),
	space(::SpaceLabel, Math::Space3d())
{
};

TrimCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
}

std::string TrimCommand::getName()
{
	return ::TrimCommandLabel;
}

void TrimCommand::execute(World* world)
{
	auto shape = world->getObjects()->findSceneById<IShapeScene*>(args.shapeId.getValue());
	auto space = args.space.getValue();
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
		auto newId = world->getObjectFactory()->createParticleSystemScene(positions, attr, "Trimmed")->getId();
		results.newId.setValue(newId);
	}
}
