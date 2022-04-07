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

#include "../CrystalPhysics/MVP/MVPParticleBuilder.h"
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
	MVPParticleBuilder pbuilder;
	const auto radius = 0.20;
	const auto length = radius * 1.00;
	std::vector<MVPVolumeParticle*> mvps;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
				const auto p = Vector3dd(i * length, j * length, k * length);
				auto mp = pbuilder.create(p, length, 1.0f);
				mvps.push_back(mp);
				//				mp->distributePoints(3, 3, 3, 1.00f);
//				fluidScene->addParticle(mp);
			}
		}
	}

	auto world = getWorld();

	MVPSurfaceBuilder builder;
	builder.build(mvps, 3, thresholdView.getValue());

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