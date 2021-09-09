#include "LinearOctreeView.h"

#include "../CrystalSpace/LinearOctree.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "../../Crystal/Scene/WireFrameScene.h"

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
	const Sphere3dd sphere(Vector3dd(5, 5, 5), 2.5);
	builder.add(sphere, 32, 32);
	auto mesh = builder.build();

	const Box3d space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));

	const auto faces = builder.getFaces();
	const auto positions = builder.getPositions();
	LinearOctree treeOperator;
	treeOperator.init(space, 4);

	/*
	for (const auto& f : faces) {
		const auto t = f.toTriangle(positions);
		auto item = new LinearOctreeItem(t);
		treeOperator.add(item);
	}
	*/
	Box3dd b1(Vector3dd(8, 8, 8), Vector3dd(8, 8, 8));
	auto item1 = new LinearOctreeItem(b1);
	treeOperator.add(item1);

	Box3dd b2(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	auto item2 = new LinearOctreeItem(b2);
	treeOperator.add(item2);

	Box3dd b3(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1));
	auto item3 = new LinearOctreeItem(b3);
	treeOperator.add(item3);

	const auto& table = treeOperator.getTable();
	std::vector<Box3dd> boxes;
	for (int i = 0; i < table.size(); ++i) {
		if (table[i] != nullptr) {
			const auto b = treeOperator.calculateAABB(LinearOctreeIndex(i));
			boxes.push_back(b);
		}
	}

	WireFrameBuilder wfBuilder;
	/*
	auto children = octree.toSerialList();
	for (auto c : children) {
		wfBuilder.build(c->getSpace());
	}
	*/
	for (auto b : boxes) {
		wfBuilder.build(b);
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