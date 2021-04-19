#include "MarchingCubesView.h"

#include "../CrystalSpace/MarchingCubesAlgo.h"
#include "../../Crystal/Scene/VolumeScene.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Math/Gaussian.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Space;

MarchingCubesView::MarchingCubesView(World* model, Canvas* canvas) :
	IOkCancelView("MarchingCubes", model, canvas),
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

void MarchingCubesView::onShow()
{
	for (auto& v : values) {
		v.show();
	}
}

void MarchingCubesView::onOk()
{
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	Volume<double> v(box, { 10, 10, 10 });

	const auto center = box.getCenter();
	const auto radius = 5.0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto distanceSquared = Math::getDistanceSquared(v.getCellPosition(i, j, k), center);
				if (distanceSquared < radius * radius) {
					const auto distance = ::sqrt(distanceSquared);
					const auto value = 1.0 - distance / radius;
					v.setValue(i, j, k, value);
				}
			}
		}
	}

	MarchingCubesAlgo algo;
	algo.build(v, 0.30);
	const auto& triangles = algo.getTriangles();
	PolygonMeshBuilder builder;
	for (const auto& t : triangles) {
		builder.add(t);
	}
	//getWorld()->getO
	//builder.pushCurrentFaceGroup();
	//getWorld()->getObjectFactory()->createPolygonMeshScene(builder.(), "MarchingCubes");
	//getWorld()->updateViewModel();
}