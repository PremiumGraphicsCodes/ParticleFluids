#include "SpaceHashButton.h"

#include "../CrystalAlgo/SpaceHash.h"

using namespace Crystal::UI;
using namespace Crystal::Algo;

SpaceHashButton::SpaceHashButton(Repository* model, Canvas* canvas) :
	IPopupButton("SpaceHash", model, canvas)
{
	SpaceHash space(1.0f, 10000);
}

void SpaceHashButton::onShow()
{
	/*
	ImGui::InputFloat3("Min", &min[0]);
	ImGui::InputFloat3("Max", &max[0]);
	ImGui::InputFloat3("Dx", &dx[0]);
	*/
}

void SpaceHashButton::onOk()
{
/*
	std::vector<Vector3df> positions;
	for (double x = min.x; x < max.x; x += dx[0]) {
		for (double y = min.y; y < max.y; y += dx[1]) {
			for (double z = min.z; z < max.z; z += dx[2]) {
				positions.push_back(Vector3df(x, y, z));
			}
		}
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), 100.0f, "Box");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
	*/
}

