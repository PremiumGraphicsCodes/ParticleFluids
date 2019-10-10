#include "Box3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Box3dView::Box3dView(const std::string& name) :
	IView(name),
	minView("Min", Vector3dd(0, 0, 0)),
	maxView("Max", Vector3dd(1, 1, 1))
{
	add(&minView);
	add(&maxView);
}

Box3d Box3dView::getValue() const
{
	return Box3d(minView.getValue(), maxView.getValue());
}

void Box3dView::setValue(const Box3d& value)
{
	minView.setValue(value.getMin());
	maxView.setValue(value.getMax());
}