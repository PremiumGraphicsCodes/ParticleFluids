#include "OctreeView.h"

#include "../CrystalSpace/Octree.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

OctreeView::OctreeView(World* model, Canvas* canvas) :
	IOkCancelView("Octree", model, canvas),
	positionButton("Position", model, canvas),
	objectButton("Object", model, canvas)
{
}

void OctreeView::onShow()
{
	positionButton.show();
	objectButton.show();
}

void OctreeView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	builder.add(box, 2, 2, 2);
	//const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	//builder.add(sphere, 32, 32);
	auto mesh = builder.build();


	Octree octree;

	//octree.add()
	/*
		std::vector<Vector3df> positions;
		for (double x = min.x; x < max.x; x += dx[0]) {
			for (double y = min.y; y < max.y; y += dx[1]) {
				for (double z = min.z; z < max.z; z += dx[2]) {
					positions.push_back(Vector3df(x, y, z));
				}
			}
		}
		getModel()->getObjects()->getParticleSystems()->addObject(positions, ColorRGBAf(1, 1, 1, 1), 100.0f, "Box");
		getCanvas()->setViewModel(getModel()->toViewModel());
		getCanvas()->fitCamera(getModel()->getBoundingBox());
		*/
}