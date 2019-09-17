#include "Box3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Box3dView::Box3dView(const std::string& name) :
	IWindow(name),
	min("Min", Math::Vector3dd(0, 0, 0)),
	max("Max", Math::Vector3dd(1, 1, 1))
{
}

void Box3dView::onShow()
{
	min.show();
	max.show();
}

Box3d Box3dView::getValue() const
{
	return Math::Box3d(min.getValue(), max.getValue());
}