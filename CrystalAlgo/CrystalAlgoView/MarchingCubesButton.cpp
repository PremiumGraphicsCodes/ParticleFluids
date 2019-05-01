#include "MarchingCubesButton.h"

#include "../CrystalAlgo/MarchingCubesAlgo.h"

using namespace Crystal::Math;
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
	MarchingCubesAlgo::MCCell cell;
	cell.position[0] = Vector3dd(0, 0, 0);
	cell.position[1] = Vector3dd(1, 0, 0);
	cell.position[2] = Vector3dd(1, 1, 0);
	cell.position[3] = Vector3dd(0, 1, 0);
	cell.position[4] = Vector3dd(0, 0, 1);
	cell.position[5] = Vector3dd(1, 0, 1);
	cell.position[6] = Vector3dd(1, 1, 1);
	cell.position[7] = Vector3dd(0, 1, 1);

	cell.value[0] = 0.0;
	cell.value[1] = 100.0;
	cell.value[2] = 0.0;
	cell.value[3] = 0.0;
	cell.value[4] = 0.0;
	cell.value[5] = 0.0;
	cell.value[6] = 0.0;
	cell.value[7] = 0.0;

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

