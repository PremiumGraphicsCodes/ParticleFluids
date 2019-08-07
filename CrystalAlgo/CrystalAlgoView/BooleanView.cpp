#include "BooleanView.h"

#include "../CrystalAlgo/BooleanAlgo.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Algo;

BooleanView::BooleanView(RootScene* model, Canvas* canvas) :
	IOkCancelView("Boolean", model, canvas),
	objectButton1("Polygon1", model, canvas),
	objectButton2("Polygon2", model, canvas)
{
}

void BooleanView::show()
{
	objectButton1.show();
	objectButton2.show();
}

void BooleanView::onOk()
{
	auto polygon1 = static_cast<Crystal::Scene::PolygonMeshScene*>( getRepository()->getObjects()->findSceneById(objectButton1.getId()) );
	auto polygon2 = static_cast<Crystal::Scene::PolygonMeshScene*>( getRepository()->getObjects()->findSceneById(objectButton2.getId()) );
	if (polygon1 == nullptr || polygon2 == nullptr) {
		return;
	}
	BooleanAlgo algo;
	algo.calculateDifference(*polygon1->getShape(), *polygon2->getShape());

	polygon1->setVisible(false);
	polygon2->setVisible(false);

	getRepository()->getObjectFactory()->createPolygonMeshScene(algo.getResult(), "Intersection");
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
