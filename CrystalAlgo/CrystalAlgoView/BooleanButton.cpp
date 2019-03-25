#include "BooleanButton.h"

#include "../CrystalAlgo/BooleanAlgo.h"

using namespace Crystal::UI;
using namespace Crystal::Algo;

BooleanButton::BooleanButton(Repository* model, Canvas* canvas) :
	IPopupButton("Boolean", model, canvas),
	objectButton1("Polygon1", model, canvas),
	objectButton2("Polygon2", model, canvas)
{
}

void BooleanButton::onShow()
{
	objectButton1.show();
	objectButton2.show();
}

void BooleanButton::onOk()
{
	auto polygon1 = getModel()->getObjects()->getPolygonMeshes()->findObjectById(objectButton1.getId()).getShape();
	auto polygon2 = getModel()->getObjects()->getPolygonMeshes()->findObjectById(objectButton2.getId()).getShape();
	if (polygon1 == nullptr || polygon2 == nullptr) {
		return;
	}
	BooleanAlgo algo;
	algo.calculateIntersection(*polygon1, *polygon2);
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

void BooleanButton::onCancel()
{
}

