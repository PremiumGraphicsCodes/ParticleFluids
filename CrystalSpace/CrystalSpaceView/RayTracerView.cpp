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
	RayTracer rayTracer;
	rayTracer.build(Box3dd(Vector3dd(0,0,0), Vector3dd(10,10,10)),4);

	/*
	Box3dd b1(Vector3dd(8, 8, 8), Vector3dd(9, 9, 9));
	auto item1 = new LinearOctreeItem(b1);
	rayTracer.add(item1);

	Box3dd b2(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	auto item2 = new LinearOctreeItem(b2);
	rayTracer.add(item2);

	Box3dd b3(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1));
	auto item3 = new LinearOctreeItem(b3);
	rayTracer.add(item3);
	*/

	Ray3d ray(Vector3dd(0.1, 0.1, 0.1), Vector3dd(10, 10, 10));
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