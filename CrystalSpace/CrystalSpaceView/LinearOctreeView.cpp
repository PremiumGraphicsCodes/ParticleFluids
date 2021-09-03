#include "LinearOctreeView.h"

#include "../CrystalSpace/LinearOctree.h"

#include "../../Crystal/Math/Sphere3d.h"
//#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

//#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

LinearOctreeView::LinearOctreeView(World* model, Canvas* canvas) :
	IOkCancelView("LinearOctree", model, canvas)
{
}

void LinearOctreeView::onOk()
{
	PolygonMeshBuilder builder;
	//const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	//builder.add(box, 2, 2, 2);
	const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	builder.add(sphere, 32, 32);
	auto mesh = builder.build();

	const auto faces = builder.getFaces();
	const auto positions = builder.getPositions();
	LinearOctree octree(mesh->getBoundingBox());
	/*
	for (const auto& f : faces) {
		const auto t = f.toTriangle(positions);
		auto item = new IOctreeItem(t);
		octree.add(item);
	}

	WireFrameBuilder wfBuilder;
	auto children = octree.toSerialList();
	for (auto c : children) {
		wfBuilder.build(c->getSpace());
	}

	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 1, 1, 1);
	attr.width = 1.0;
	auto scene = new WireFrameScene(getWorld()->getNextSceneId(), "", std::move(wf), attr);
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	*/
}