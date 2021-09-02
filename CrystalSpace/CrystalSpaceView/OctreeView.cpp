#include "OctreeView.h"

#include "../CrystalSpace/Octree.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

OctreeView::OctreeView(World* model, Canvas* canvas) :
	IOkCancelView("Octree", model, canvas)
{
}

void OctreeView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	builder.add(box, 2, 2, 2);
	//const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	//builder.add(sphere, 32, 32);
	auto mesh = builder.build();

	const auto faces = builder.getFaces();
	const auto positions = builder.getPositions();
	Octree octree(mesh->getBoundingBox(),0);
	for (const auto& f : faces) {
		const auto t = f.toTriangle(positions);
		auto item = new IOctreeItem(t);
		octree.add(item);
	}
}