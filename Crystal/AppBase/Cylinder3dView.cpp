#include "Cylinder3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Cylinder3dView::Cylinder3dView(const std::string& name) :
	IWindow(name),
	center("Center", Math::Vector3dd(0, 0, 0)),
	radius("Radius", 1.0),
	height("Height", 1.0)
{
}

void Cylinder3dView::onShow()
{
	center.show();
	radius.show();
	height.show();
}

Cylinder3d Cylinder3dView::getValue() const
{
	return Math::Cylinder3d(radius.getValue(), height.getValue(), center.getValue());
}
