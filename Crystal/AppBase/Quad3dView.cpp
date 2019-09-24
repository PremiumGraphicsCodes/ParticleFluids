#include "Quad3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Quad3dView::Quad3dView(const std::string& name) :
	IView(name),
	origin("Origin", Math::Vector3dd(0, 0, 0)),
	uvec("UVec", Math::Vector3dd(1, 0, 0)),
	vvec("VVec", Math::Vector3dd(0, 1, 0))
{
	add(&origin);
	add(&uvec);
	add(&vvec);
}

Quad3d Quad3dView::getValue() const
{
	return Math::Quad3d(origin.getValue(), uvec.getValue(), vvec.getValue());
}
