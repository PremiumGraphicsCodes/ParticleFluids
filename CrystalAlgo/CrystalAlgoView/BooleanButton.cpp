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
	auto polygon1 = static_cast<Crystal::Scene::PolygonMeshScene*>( getModel()->getObjects()->findSceneById(objectButton1.getId()) );
	auto polygon2 = static_cast<Crystal::Scene::PolygonMeshScene*>( getModel()->getObjects()->findSceneById(objectButton2.getId()) );
	if (polygon1 == nullptr || polygon2 == nullptr) {
		return;
	}
	BooleanAlgo algo;
	algo.calculateDifference(*polygon1->getShape(), *polygon2->getShape());

	polygon1->setVisible(false);
	polygon2->setVisible(false);

	getModel()->getObjectFactory()->createPolygonMeshScene(algo.getResult(), "Intersection");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void BooleanButton::onCancel()
{
}

