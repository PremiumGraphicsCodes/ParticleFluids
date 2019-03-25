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
	Graphics::Material mat;
	getModel()->getObjects()->getPolygonMeshes()->addObject(algo.getResult(), mat, "Intersection");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void BooleanButton::onCancel()
{
}

