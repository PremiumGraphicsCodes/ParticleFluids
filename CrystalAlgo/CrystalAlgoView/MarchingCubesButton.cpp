#include "MarchingCubesButton.h"

#include "../CrystalAlgo/MarchingCubesAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

MarchingCubesButton::MarchingCubesButton(Repository* model, Canvas* canvas) :
	IPopupButton("MarchingCubes", model, canvas),
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
	for (auto& v : values) {
		v.show();
	}
}

void MarchingCubesButton::onOk()
{
	MCCell cell;
	cell.vertices[0].position = Vector3dd(0, 0, 0);
	cell.vertices[1].position = Vector3dd(1, 0, 0);
	cell.vertices[2].position = Vector3dd(1, 1, 0);
	cell.vertices[3].position = Vector3dd(0, 1, 0);
	cell.vertices[4].position = Vector3dd(0, 0, 1);
	cell.vertices[5].position = Vector3dd(1, 0, 1);
	cell.vertices[6].position = Vector3dd(1, 1, 1);
	cell.vertices[7].position = Vector3dd(0, 1, 1);

	for (int i = 0; i < 8; ++i) {
		cell.vertices[i].value = values[i].getValue();
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