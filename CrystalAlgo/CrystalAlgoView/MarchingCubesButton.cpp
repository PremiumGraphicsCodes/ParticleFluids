#include "MarchingCubesButton.h"

#include "../CrystalAlgo/MarchingCubesAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

MarchingCubesButton::MarchingCubesButton(Repository* model, Canvas* canvas) :
	IPopupButton("MarchingCubes", model, canvas),
	objectButton1("ParticleSystem", model, canvas, Model::ObjectType::ParticleSystemObject),
	values({
		DoubleView("Value0", 0),
		DoubleView("Value1", 100),
		DoubleView("Value2", 0),
		DoubleView("Value3", 0),
		DoubleView("Value4", 0),
		DoubleView("Value5", 0),
		DoubleView("Value6", 0),
		DoubleView("Value7", 0),
		})
{
}

void MarchingCubesButton::onShow()
{
	objectButton1.show();
	for (auto& v : values) {
		v.show();
	}
}

void MarchingCubesButton::onOk()
{
	MarchingCubesAlgo::MCCell cell;
	cell.position[0] = Vector3dd(0, 0, 0);
	cell.position[1] = Vector3dd(1, 0, 0);
	cell.position[2] = Vector3dd(1, 1, 0);
	cell.position[3] = Vector3dd(0, 1, 0);
	cell.position[4] = Vector3dd(0, 0, 1);
	cell.position[5] = Vector3dd(1, 0, 1);
	cell.position[6] = Vector3dd(1, 1, 1);
	cell.position[7] = Vector3dd(0, 1, 1);

	for (int i = 0; i < 8; ++i) {
		cell.value[i] = values[i].getValue();
	}

	MarchingCubesAlgo algo;
	algo.march(cell, 50.0);
	const auto& triangles = algo.getTriangles();
	Crystal::Shape::PolygonMeshBuilder builder;
	builder.build(triangles);
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), 1, "MarchingCubes");
	getCanvas()->setViewModel(getModel()->toViewModel());
}

void MarchingCubesButton::onCancel()
{
}

