#include "SPHSurfaceBuilderView.h"

#include "../CrystalPhysics/SurfaceConstruction/SPHSurfaceBuilder.h"

#include "Crystal/Shape/Particle.h"
#include "Crystal/Shape/WireFrameBuilder.h"

#include "CrystalScene/Scene/WireFrameScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

#include "CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include "Crystal/Math/Sphere3d.h"
#include "Crystal/Math/Ellipsoid3d.h"

#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"
//#include "Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

namespace {
	constexpr auto tolerance = 1.0e-12;

	void build(const Sphere3dd& sphere, const int unum, const int vnum, const Matrix3dd& m, WireFrameBuilder& wfBuilder)
	{
		const auto du = 1.0 / static_cast<double>(unum);
		const auto dv = 1.0 / static_cast<double>(vnum);

		std::vector<std::vector<int>> grid;
		for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
			std::vector<int> g;
			for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
				auto p = sphere.getPosition(u, v);
				p -= sphere.getCenter();
				p = m * p * glm::determinant(m);
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
	cellLengthView("CellLength"),
	colorMapView("ColorMap")
{
	searchRadiusView.setValue(1.0f);
	add(&searchRadiusView);
	cellLengthView.setValue(0.5f);
	add(&cellLengthView);
	add(&colorMapView);
}

void SPHSurfaceBuilderView::onOk()
{
	std::vector<Vector3dd> positions;

	/*
	Sphere3d sphere(Vector3dd(0,0,0), 10);
	for (auto u = 0.0; u < 1.0; u += 0.1) {
		for (auto v = 0.0; v < 1.0; v +=0.1) {
			for (auto w = 0.0; w < 1.0; w += 0.1) {
				positions.push_back( sphere.getPosition(u, v, w) );
			}
		}
	}
	*/
	//sphere.getPosition()

	const Sphere3d sphere(Vector3dd(0, 0, 0), 5.0);
	const Box3d box = sphere.getBoundingBox();
	const auto center = sphere.getCenter();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto u = i / 10.0;
				const auto v = j / 10.0;
				const auto w = k / 10.0;
				const auto p = box.getPosition(u,v,w);
				if (sphere.isInside(p)) {
					positions.push_back(p);
				}
			}
		}
	}

	auto world = getWorld();

	SPHSurfaceBuilder builder;
	builder.buildAnisotoropic(positions, searchRadiusView.getValue(), cellLengthView.getValue());

	MarchingCubesAlgo mcAlgo;
	mcAlgo.build(*builder.getVolume(), 1.0e-3);

	//PolygonMeshBuilder pmBuilder;
	auto mesh = std::make_unique<TriangleMesh>();
	const auto triangles = mcAlgo.getTriangles();
	for (const auto& t : triangles) {
		mesh->addFace(TriangleFace(t));
	}
	auto scene = new TriangleMeshScene(getWorld()->getNextSceneId(), "", std::move(mesh));

	scene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(scene);
	/*
	WireFrameBuilder wfBuilder;

	auto& particles = builder.getParticles();
	for (auto& p : particles) {
		const auto m = p->getMatrix();
		Sphere3d s(p->getPosition(), 1.0);
		//wfBuilder.build(s, 10, 10);
		::build(s, 10, 10, m,  wfBuilder);
	}
	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = glm::vec4(1, 1, 1, 1);
	attr.width = 1.0f;
	WireFrameScene* wfScene = new WireFrameScene(getWorld()->getNextSceneId(), "WF", std::move(wf), attr);
	wfScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	getWorld()->getScenes()->addScene(wfScene);
	*/

	/*
	auto volume = builder.getVolume();
	SparseVolumeScene* svScene = new SparseVolumeScene(getWorld()->getNextSceneId(), "Vol", std::move(volume));
	auto presenter = svScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	colorMap.setMax(1.0f);
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