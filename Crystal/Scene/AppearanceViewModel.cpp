#include "AppearanceViewModel.h"

#include "AppearanceObjectRepository.h"
#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void AppearanceViewModel::add(AppearanceObjectRepository& appearances)
{
	add(*appearances.getMaterials());
}

void AppearanceViewModel::add(const MaterialObjectRepository& materials)
{
	const auto& ms = materials.getMaterials();
	for (const auto& m : ms) {
		auto mm = m->getMaterial();
		materialBuffer.add(*mm);
	}
}
