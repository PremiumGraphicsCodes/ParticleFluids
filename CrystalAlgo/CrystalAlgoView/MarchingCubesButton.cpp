#include "MarchingCubesButton.h"

#include "../CrystalAlgo/MarchingCubesAlgo.h"
#include "../../Crystal/Shape/Volume.h"
#include "../../Crystal/Math/Gaussian.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
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
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1));
	/*
	const auto& center = box.getCenter();
	const auto radius = 2.0;
	Volume volume(5, 5, 5, box);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 5; ++k) {
				volume.set()
			}
		}
	}
	*/

	Volume volume(32, 32, 32, box);

	auto function = [](double distance) {
		Gaussian gaussian;
		return gaussian.getValue(distance);
	};
	volume.add(function);


	MarchingCubesAlgo algo;
	algo.build(volume, 0.30);
	const auto& triangles = algo.getTriangles();
	Crystal::Shape::PolygonMeshBuilder builder;
	for (const auto& t : triangles) {
		builder.add(t);
	}
	builder.build();
	getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), 1, "MarchingCubes");
	getCanvas()->setViewModel(getModel()->toViewModel());
}

void MarchingCubesButton::onCancel()
{
}