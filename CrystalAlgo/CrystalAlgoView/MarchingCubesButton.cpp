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
	MarchingCubesAlgo::GRIDCELL cell;
	cell.p[0] = Vector3dd(0, 0, 0);
	cell.p[1] = Vector3dd(1, 0, 0);
	cell.p[2] = Vector3dd(1, 1, 0);
	cell.p[3] = Vector3dd(0, 1, 0);
	cell.p[4] = Vector3dd(0, 0, 1);
	cell.p[5] = Vector3dd(1, 0, 1);
	cell.p[6] = Vector3dd(1, 1, 1);
	cell.p[7] = Vector3dd(0, 1, 1);

	cell.val[0] = 0.0;
	cell.val[1] = 100.0;
	cell.val[2] = 0.0;
	cell.val[3] = 0.0;
	cell.val[4] = 0.0;
	cell.val[5] = 0.0;
	cell.val[6] = 0.0;
	cell.val[7] = 0.0;

	MarchingCubesAlgo algo;
	algo.march(cell, 50.0);
	const auto& triangles = algo.getTriangles();
	Crystal::Shape::PolygonMesh* mesh = new Crystal::Shape::PolygonMesh(triangles);
	getModel()->getObjects()->getPolygonMeshes()->addObject(mesh, 1, "MarchingCubes");
	getCanvas()->setViewModel(getModel()->toViewModel());
}

void MarchingCubesButton::onCancel()
{
}

