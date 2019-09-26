#include "PSSphereView.h"

#include "../Math/Sphere3d.h"
#include "../Graphics/ColorRGBA.h"

#include "../Scene/ParticleSystemScene.h"
#include "../Command/Command.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::UI;

PSSphereView::PSSphereView(World* model, Canvas* canvas) :
	IOkCancelView("PSSphere", model, canvas),
	sphere("Sphere"),
	attribute("Attribute"),
	count("Count", 10000)
{
	add(&sphere);
	add(&attribute);
	add(&count);
}

void PSSphereView::onOk()
{
	const auto& shape = sphere.getValue();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	std::vector<Vector3dd> positions;
	for (int i = 0; i < count.getValue(); ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		positions.push_back(shape.getPosition(Vector3dd(u, v, 1.0)));
	}
	
	Command::Command command;
	command.create("ParticleSystemAdd");
	command.setArg("Positions", positions);
	command.setArg("PointSize", attribute.getValue().size);
	command.setArg("Color", attribute.getValue().color);
	command.setArg("Name", std::string("PSSphere"));
	command.execute(getWorld());

	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
