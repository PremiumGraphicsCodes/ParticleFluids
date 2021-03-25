#include "SVSphereView.h"

#include "../../CrystalSpace/CrystalAlgo/SparseVolume.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

SVSphereView::SVSphereView(const std::string& name, World* world, Canvas* canvas) :
	ISVAddView(name, world, canvas),
	boxView("Box"),
	resolutionView("Resolution")
{
	add(&boxView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void SVSphereView::onOk()
{
	const auto box = boxView.getValue();
	const auto res = static_cast<size_t>(resolutionView.getValue());
	const std::array<int, 3> resolution = { res, res, res };
	auto v = std::make_unique<SparseVolume>(box, resolution);
	//v = std::make_unique<Volume<float>> 

	ISVAddView::addVolume(std::move(v));
}
