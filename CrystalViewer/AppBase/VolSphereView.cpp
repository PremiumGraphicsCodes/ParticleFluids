#include "VolSphereView.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

VolSphereView::VolSphereView(const std::string& name, World* world, Canvas* canvas) :
	IVolAddView(name, world, canvas),
	boxView("Box"),
	resolutionView("Resolution")
{
	add(&boxView);
	add(&resolutionView);
	resolutionView.setValue(10);
}

void VolSphereView::onOk()
{
	const auto box = boxView.getValue();
	const auto res = static_cast<size_t>( resolutionView.getValue() );
	std::array<size_t, 3> resolution = { res, res, res };
	auto v = std::make_unique<Volume<float>>(box, resolution);
	//v = std::make_unique<Volume<float>> 
	
	IVolAddView::addVolume(std::move(v));
}
