#include "Cone3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Cone3dView::Cone3dView(const std::string& name) :
	IWindow(name),
	center("Bottom", Math::Vector3dd(0, 0, 0)),
	radius("Radius", 1.0),
	height("Height", 1.0)
{
}

void Cone3dView::onShow()
{
	center.show();
	radius.show();
	height.show();
}

Cone3d Cone3dView::getValue() const
{
	return Math::Cone3d(center.getValue(), radius.getValue(), height.getValue());
}
