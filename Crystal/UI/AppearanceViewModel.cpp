#include "AppearanceViewModel.h"
#include "Repository.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void AppearanceViewModel::add(AppearanceObjectRepository& appearances)
{
	add(*appearances.getLights());
	add(*appearances.getMaterials());
}

void AppearanceViewModel::add(const LightObjectRepository& lights)
{
	const auto& ls = lights.getLights();
	for (const auto& l : ls) {
		auto ll = l->getLight();
		lightBuffer.add(*ll);
	}
}

void AppearanceViewModel::add(const MaterialObjectRepository& materials)
{
	const auto& ms = materials.getMaterials();
	for (const auto& m : ms) {
		auto mm = m->getMaterial();
		materialBuffer.add(*mm);
	}
}
