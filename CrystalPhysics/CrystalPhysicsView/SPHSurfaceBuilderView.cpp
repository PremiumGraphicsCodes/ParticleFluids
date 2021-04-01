#include "SPHSurfaceBuilderView.h"

#include "../CrystalPhysics/SPHSurfaceBuilder.h"

#include "../../Crystal/Shape/Particle.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

SPHSurfaceBuilderView::SPHSurfaceBuilderView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadiusView("SearchRadius"),
	colorMapView("ColorMap")
{
	searchRadiusView.setValue(1.0f);
	add(&searchRadiusView);
	add(&colorMapView);
}

void SPHSurfaceBuilderView::onOk()
{
	std::vector<Vector3dd> positions = 
	{
		Vector3dd(0.0, 0.0, 0.0),
		Vector3dd(0.5, 0.0, 0.0),
		Vector3dd(10.0, 10.0, 10.0),
		//Vector3dd(100.0, 100.0, 100.0)
//		Vector3dd(0.0, 0.5, 0.0),

	};

	auto world = getWorld();

	SPHSurfaceBuilder builder;
	builder.buildIsotoropic(positions, searchRadiusView.getValue());

	auto& particles = builder.getParticles();

	auto volume = builder.getVolume();
	SparseVolumeScene* svScene = new SparseVolumeScene(getWorld()->getNextSceneId(), "Vol", std::move(volume));
	auto presenter = svScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	//colorMap.setMax(0.01f);
	static_cast<SparseVolumePresenter*>(presenter)->setColorMap(colorMap);
	presenter->createView(world->getRenderer(), *world->getGLFactory());
	//volumeS

	getWorld()->getScenes()->addScene(svScene);

	/*
	WireFrameBuilder wfBuilder;
	for (const auto& p : particles) {
		wfBuilder.build()
	}
	*/
}