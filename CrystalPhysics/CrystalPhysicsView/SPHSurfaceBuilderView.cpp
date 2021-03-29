#include "SPHSurfaceBuilderView.h"

#include "../CrystalPhysics/SPHSurfaceBuilder.h"

#include "../../Crystal/Shape/Particle.h"

#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

SPHSurfaceBuilderView::SPHSurfaceBuilderView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	searchRadiusView("SearchRadius")
{
	searchRadiusView.setValue(1.0f);
	add(&searchRadiusView);
}

void SPHSurfaceBuilderView::onOk()
{
	std::vector<Vector3dd> positions = 
	{
		Vector3dd(0.0, 0.0, 0.0),
		Vector3dd(0.5, 0.0, 0.0),
		Vector3dd(10.0, 10.0, 10.0)

//		Vector3dd(0.0, 0.5, 0.0),

	};

	SPHSurfaceBuilder builder;
	builder.build(positions, searchRadiusView.getValue());

	auto particles = std::move( builder.getParticles() );

	/*
	WireFrameBuilder wfBuilder;
	for (const auto& p : particles) {
		wfBuilder.build()
	}
	*/
}