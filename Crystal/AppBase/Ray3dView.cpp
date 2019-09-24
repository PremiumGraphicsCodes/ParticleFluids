#include "Ray3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Ray3dView::Ray3dView(const std::string& name) :
	IView(name),
	origin("Origin", Math::Vector3dd(0, 0, 0)),
	direction("Direction", Math::Vector3dd(0, 0, 1))
{
	add(&origin);
	add(&direction);
}

Ray3d Ray3dView::getValue() const
{
	return Math::Ray3d(origin.getValue(), direction.getValue());
}
