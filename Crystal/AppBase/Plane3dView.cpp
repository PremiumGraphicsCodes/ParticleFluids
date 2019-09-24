#include "Plane3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Plane3dView::Plane3dView(const std::string& name) :
	IView(name),
	origin("Origin", Math::Vector3dd(0, 0, 0)),
	normal("Normal", Math::Vector3dd(0, 0, 1))
{
	add(&origin);
	add(&normal);
}

Plane3d Plane3dView::getValue() const
{
	return Math::Plane3d(origin.getValue(), normal.getValue());
}

void Plane3dView::setValue(const Plane3d& value)
{
	origin.setValue( value.getOrigin() );
	normal.setValue( value.getNormal() );
}
