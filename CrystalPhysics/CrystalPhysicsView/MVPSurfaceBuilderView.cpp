#include "MVPSurfaceBuilderView.h"

#include "../CrystalPhysics/MVPSurfaceBuilder.h"

#include "Crystal/Shape/Particle.h"
#include "Crystal/Shape/WireFrameBuilder.h"

#include "CrystalScene/Scene/WireFrameScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

#include "CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include "Crystal/Math/Sphere3d.h"
#include "Crystal/Math/Ellipsoid3d.h"

#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"
//#include "Crystal/Shape/PolygonMeshBuilder.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

MVPSurfaceBuilderView::MVPSurfaceBuilderView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleRadiusView("ParticleRadius", 1.0f),
	cellLengthView("CellLength", 1.0),
	thresholdView("Threshold", 1.0f),
	colorMapView("ColorMap")
{
	add(&particleRadiusView);
	add(&cellLengthView);
	add(&thresholdView);
	add(&colorMapView);
}

void MVPSurfaceBuilderView::onOk()
{
	std::vector<Vector3dd> positions;

	positions.emplace_back(0, 0, 0);

	CompactSpaceHash3d spaceHash;
	spaceHash.setup(1.0, 100);
	for (double x = 10; x < 20; x+=1.0) {
		for (double y = 10; y < 20; y += 1.0) {
			for (double z = 10; z < 20; z += 1.0) {
				spaceHash.add(new Particle<double>(Vector3dd(x, y, z), 1.0));
			}
		}
	}

	auto world = getWorld();

	MVPSurfaceBuilder builder;
	builder.build(spaceHash, 0.5);

	/*
	MarchingCubesAlgo mcAlgo;
	mcAlgo.march(* volume, thresholdView.getValue());
	*/

	auto mesh = std::make_unique<TriangleMesh>();
	const auto triangles = builder.getTriangles();
	for (const auto& t : triangles) {
		mesh->addFace(TriangleFace(t));
	}
	auto scene = new TriangleMeshScene(getWorld()->getNextSceneId(), "", std::move(mesh));

	scene->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(scene);

	/*
	SparseVolumeScene* svScene = new SparseVolumeScene(getWorld()->getNextSceneId(), "Vol", std::move(volume));
	auto presenter = svScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	colorMap.setMinMax(minValue, maxValue);
	static_cast<SparseVolumePresenter*>(presenter)->setColorMap(colorMap);
	presenter->createView(world->getRenderer());

	getWorld()->getScenes()->addScene(svScene);
	*/
}