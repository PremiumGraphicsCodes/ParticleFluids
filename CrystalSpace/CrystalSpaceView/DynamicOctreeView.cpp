#include "DynamicOctreeView.h"

#include "../CrystalSpace/DynamicOctree.h"

#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Shape/Particle.h"

#include "CrystalScene/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

DynamicOctreeView::DynamicOctreeView(World* model, Canvas* canvas) :
	IOkCancelView("DynamicOctree", model, canvas)
{
}

void DynamicOctreeView::onOk()
{
	Particle<float> p(Vector3dd(1, 1, 1), 1.0f);
	DynamicOctree octree(Box3dd(Vector3dd(0,0,0), Vector3dd(16,16,16)));
	octree.divide(1.0, { &p });

	WireFrameBuilder wfBuilder;
	auto children = octree.toSerialList();
	for (auto c : children) {
		wfBuilder.add(c->getBox());
	}

	auto wf = wfBuilder.createWireFrame();
	WireFrameAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 1, 1, 1);
	attr.width = 1.0;
	auto scene = new WireFrameScene(getWorld()->getNextSceneId(), "", std::move(wf), attr);
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}