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
	//	const Sphere3dd sphere(Vector3dd(0,0,0), 10);
	//	builder.add(sphere, 20, 20);
	const Box3dd box(Vector3dd(-10, -10, -10), Vector3dd(10, 10, 10));
	builder.add(box, 2, 2, 2);
	auto mesh = builder.build();

	RayTracer rayTracer;
	rayTracer.build(Box3dd(Vector3dd(0,0,0), Vector3dd(10,10,10)),4);

	const auto faces = mesh->getFaces();

	for (const auto& f : faces) {
		const auto t = f.toTriangle(mesh->getPositions());
		RayTraceItem* item = new RayTraceItem(t);
		rayTracer.add(item);
	}

	const auto dir = Vector3dd(1, 1, 1);
	Ray3d ray(Vector3dd(0.1, 0.1, 0.1), glm::normalize(dir));
	auto found = rayTracer.trace(ray, 0.5);
	found.sort();
	found.unique();

	WireFrameBuilder wfBuilder;
	for (auto f : found) {
		for (auto i : f->getItems()) {
			wfBuilder.build(i->getBoundingBox());
		}
	}

	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 1, 1, 1);
	attr.width = 1.0;
	auto scene = new WireFrameScene(getWorld()->getNextSceneId(), "", std::move(wf), attr);
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}