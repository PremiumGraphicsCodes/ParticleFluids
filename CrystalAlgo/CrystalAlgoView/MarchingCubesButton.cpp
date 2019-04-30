#include "MarchingCubesButton.h"

#include "../CrystalAlgo/MarchingCubesAlgo.h"

using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

MarchingCubesButton::MarchingCubesButton(Repository* model, Canvas* canvas) :
	IPopupButton("MarchingCubes", model, canvas),
	objectButton1("ParticleSystem", model, canvas, Model::ObjectType::ParticleSystemObject)
{
}

void MarchingCubesButton::onShow()
{
	objectButton1.show();
}

void MarchingCubesButton::onOk()
{
	/*
	auto polygon1 = getModel()->getObjects()->getPolygonMeshes()->findObjectById(objectButton1.getId());
	auto polygon2 = getModel()->getObjects()->getPolygonMeshes()->findObjectById(objectButton2.getId());
	if (polygon1 == nullptr || polygon2 == nullptr) {
		return;
	}
	BooleanAlgo algo;
	algo.calculateDifference(*polygon1->getShape(), *polygon2->getShape());

	polygon1->setVisible(false);
	polygon2->setVisible(false);

	getModel()->getObjects()->getPolygonMeshes()->addObject(algo.getResult(), 1, "Intersection");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
	*/
}

void MarchingCubesButton::onCancel()
{
}

