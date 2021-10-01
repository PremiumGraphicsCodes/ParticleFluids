#include "MarchingCubesView.h"

#include "../CrystalSpace/MarchingCubesAlgo.h"
#include "CrystalScene/Scene/VolumeScene.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"
//#include "../../Crystal/Math/Gaussian.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Space;

MarchingCubesView::MarchingCubesView(World* model, Canvas* canvas) :
	IOkCancelView("MarchingCubes", model, canvas)
{
}

/*
void MarchingCubesView::onShow()
{
}
*/

void MarchingCubesView::onOk()
{
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	//Volume<double> v(box, { 100, 100, 100 });

	SparseVolumed v(box, { 100,100,100 });

	const auto center = box.getCenter();
	const auto radius = 5.0;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 100; ++k) {
				const auto distanceSquared = Math::getDistanceSquared(v.getPositionAt({ i, j, k }), center);
				if (distanceSquared < radius * radius) {
					const auto distance = ::sqrt(distanceSquared);
					const auto value = 1.0 - distance / radius;
					auto n = v.createNode({ i,j,k });
					n->setValue(value);
					//v.setValue(i, j, k, value);
				}
			}
		}
	}

	MarchingCubesAlgo algo;
	algo.build(v, 0.30f);
	const auto& triangles = algo.getTriangles();
	PolygonMeshBuilder builder;
	for (const auto& t : triangles) {
		builder.add(t);
	}
	auto scene = new PolygonMeshScene(getWorld()->getNextSceneId(), "", std::move(builder.build()));

	PolygonMeshScene::FaceGroup group(builder.getFaces(), nullptr);
	scene->addGroup(group);

	scene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(scene);
	//builder.pushCurrentFaceGroup();
	//getWorld()->getObjectFactory()->createPolygonMeshScene(builder.(), "MarchingCubes");
	//getWorld()->updateViewModel();
}