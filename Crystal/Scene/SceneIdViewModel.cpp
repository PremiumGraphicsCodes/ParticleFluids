#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void SceneIdViewModel::add(Scene& objects)
{
	const auto& particleSystems = objects.getFactory()->getParticleSystems();
	for (auto ps : particleSystems) {
		ps->addViewModel(*this);
	}
	const auto& wires = objects.getFactory()->getWireFrames();
	for (auto wf : wires) {
		wf->addViewModel(*this);
	}
	const auto& polygons = objects.getFactory()->getPolygonMeshes();
	for (auto p : polygons) {
		p->addViewModel(*this);
	}
}
