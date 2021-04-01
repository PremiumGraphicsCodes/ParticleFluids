#include "SPHSurfaceBuilderView.h"

#include "../CrystalPhysics/SPHSurfaceBuilder.h"

#include "../../Crystal/Shape/Particle.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

#include "../../Crystal/Scene/WireFrameScene.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Math/Ellipsoid3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

namespace {
	constexpr auto tolerance = 1.0e-12;

	void build(const Sphere3d& sphere, const int unum, const int vnum, const Matrix3dd& m, WireFrameBuilder& wfBuilder)
	{
		const auto du = 1.0 / static_cast<double>(unum);
		const auto dv = 1.0 / static_cast<double>(vnum);

		std::vector<std::vector<int>> grid;
		for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
			std::vector<int> g;
			for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
				auto p = sphere.getPosition(u, v);
				p -= sphere.getCenter();
				p = m * p;
				p += sphere.getCenter();
				g.push_back(wfBuilder.createPosition(p));
			}
			grid.push_back(g);
		}
		for (int i = 0; i < grid.size() - 1; ++i) {
			for (int j = 0; j < grid[i].size() - 1; ++j) {
				const auto v1 = grid[i][j];
				const auto v2 = grid[i + 1][j];
				const auto v3 = grid[i + 1][j + 1];
				const auto v4 = grid[i][j + 1];
				wfBuilder.addEdge(WireFrameEdge(v1, v2));
				wfBuilder.addEdge(WireFrameEdge(v2, v3));
				wfBuilder.addEdge(WireFrameEdge(v3, v4));
				wfBuilder.addEdge(WireFrameEdge(v4, v1));
			}
		}
	}
}

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
//		Vector3dd(0.0, 0.0, 0.0),
//		Vector3dd(0.5, 0.0, 0.0),
		//Vector3dd(10.0, 10.0, 10.0),
		//Vector3dd(100.0, 100.0, 100.0)
//		Vector3dd(0.0, 0.5, 0.0),

	};

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				positions.push_back(Vector3dd(0.25 * i, 0.25 * j, 0.25 * k));
			}
		}
	}

	auto world = getWorld();

	SPHSurfaceBuilder builder;
	builder.buildAnisotoropic(positions, searchRadiusView.getValue());

	WireFrameBuilder wfBuilder;

	auto& particles = builder.getParticles();
	for (auto& p : particles) {
		const auto m = p->matrix;
		Sphere3d s(p->getPosition(), 1.0);
		//wfBuilder.build(s, 10, 10);
		::build(s, 10, 10, m,  wfBuilder);
	}
	//WireFrame()
	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = glm::vec4(1, 1, 1, 1);
	attr.width = 1.0f;
	WireFrameScene* wfScene = new WireFrameScene(getWorld()->getNextSceneId(), "WF", std::move(wf), attr);
	wfScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	getWorld()->getScenes()->addScene(wfScene);

	/*
	auto volume = builder.getVolume();
	SparseVolumeScene* svScene = new SparseVolumeScene(getWorld()->getNextSceneId(), "Vol", std::move(volume));
	auto presenter = svScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	//colorMap.setMax(0.01f);
	static_cast<SparseVolumePresenter*>(presenter)->setColorMap(colorMap);
	presenter->createView(world->getRenderer(), *world->getGLFactory());

	getWorld()->getScenes()->addScene(svScene);
	*/

	/*
	WireFrameBuilder wfBuilder;
	for (const auto& p : particles) {
		wfBuilder.build()
	}
	*/
}