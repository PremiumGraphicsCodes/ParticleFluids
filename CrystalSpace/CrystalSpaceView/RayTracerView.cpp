#include "RayTracerView.h"

#include "../CrystalSpace/RayTracer.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

RayTracerView::RayTracerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	maxLevel("MaxLevel", 4)
{
	add(&maxLevel);
}

void RayTracerView::onOk()
{
	PolygonMeshBuilder builder;
	const Sphere3dd sphere(Vector3dd(5,5,5), 5);
	builder.add(sphere, 20, 20);
	//const Box3dd box(Vector3dd(-10, -10, -10), Vector3dd(10, 10, 10));
	//builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	{
		WireFrameBuilder wfBuilder;
		wfBuilder.build(sphere, 20, 20);
		auto wf = wfBuilder.createWireFrame();
		WireFrameAttribute attr;
		attr.color = Crystal::Graphics::ColorRGBAf(0, 0, 1, 1);
		attr.width = 1.0;
		auto scene = new WireFrameScene(getWorld()->getNextSceneId(), "", std::move(wf), attr);
		getWorld()->getScenes()->addScene(scene);

		auto presenter = scene->getPresenter();
		presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	}

	RayTracer rayTracer;
	rayTracer.build(Box3dd(Vector3dd(0,0,0), Vector3dd(10,10,10)),4);

	const auto faces = mesh->getFaces();

	for (const auto& f : faces) {
		const auto t = f.toTriangle(mesh->getPositions());
		RayTraceItem* item = new RayTraceItem(t);
		rayTracer.add(item);
	}

	const auto origin = Vector3dd(0.1, 0.1, 0.1);
	const auto dir = Vector3dd(1, 1, 1);
	const Ray3d ray(origin, glm::normalize(dir));
	rayTracer.trace(ray, 0.5);
	auto found = rayTracer.getCells();
	found.sort();
	found.unique();

	auto indices = rayTracer.getIndices();
	indices.sort();
	indices.unique();

	WireFrameBuilder wfBuilder;
	const auto& octree = rayTracer.getOctree();
	const auto& table = octree.getTable();
	for (auto i : indices) {
		const auto b = octree.calculateAABB(i);
		wfBuilder.build(b);
	}

	rayTracer.findCollisions(ray, found);

	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 1, 1, 1);
	attr.width = 1.0;
	auto scene = new WireFrameScene(getWorld()->getNextSceneId(), "", std::move(wf), attr);
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}