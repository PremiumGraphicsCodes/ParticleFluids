#include "SVSphereView.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

SVSphereView::SVSphereView(const std::string& name, World* world, Canvas* canvas) :
	ISVAddView(name, world, canvas),
	sphereView("Sphere"),
	resolutionView("Resolution")
{
	add(&sphereView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void SVSphereView::onOk()
{
	const auto sphere = sphereView.getValue();
	const auto res = static_cast<size_t>(resolutionView.getValue());
	const std::array<int, 3> resolution = { res, res, res };
	auto sv = std::make_unique<SparseVolumed>(sphere.getBoundingBox(), resolution);

	const auto center = sphere.getCenter();
	const auto rad = sphere.getRadius();
	for (int ix = 0; ix < resolution[0]; ++ix) {
		for (int iy = 0; iy < resolution[1]; ++iy) {
			for (int iz = 0; iz < resolution[2]; ++iz) {
				const std::array<int,3> index = { ix, iy, iz };
				const auto p = sv->getPositionAt(index);
				if(Crystal::Math::getDistanceSquared(p, center) < rad * rad) {
					const auto d = Crystal::Math::getDistance(p, center) / rad;
					sv->createNode(index);
					auto n = sv->findNode(index);
					n->setValue(d);
				}
			}
		}
	}

	//v = std::make_unique<Volume<float>> 

	ISVAddView::addVolume(std::move(sv));
}
