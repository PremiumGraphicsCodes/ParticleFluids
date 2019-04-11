#include "Box3d.h"

using namespace Crystal::Math;

Box3d::Box3d(const Vector3dd& pointX, const Vector3dd& pointY)
{
	const auto x = std::min<double>(pointX.x, pointY.x);
	const auto y = std::min<double>(pointX.y, pointY.y);
	const auto z = std::min<double>(pointX.z, pointY.z);
	this->start = Vector3dd(x, y, z);
	const auto endX = std::max<double>(pointX.x, pointY.x);
	const auto endY = std::max<double>(pointX.y, pointY.y);
	const auto endZ = std::max<double>(pointX.z, pointY.z);
	this->end = Vector3dd(endX, endY, endZ);
	assert(isValid());
}

void Box3d::add(const Vector3dd& v)
{
	const auto x = std::min<double>(getMinX(), v.x);
	const auto y = std::min<double>(getMinY(), v.y);
	const auto z = std::min<double>(getMinZ(), v.z);
	start = Vector3dd(x, y, z);

	const auto endX = std::max<double>(end.x, v.x);
	const auto endY = std::max<double>(end.y, v.y);
	const auto endZ = std::max<double>(end.z, v.z);
	end = Vector3dd(endX, endY, endZ);
}

void Box3d::add(const Box3d& b)
{
	const auto sx = std::min<double>(getMinX(), b.getMinX());
	const auto sy = std::min<double>(getMinY(), b.getMinY());
	const auto sz = std::min<double>(getMinZ(), b.getMinZ());
	this->start = Vector3dd(sx, sy, sz);

	const auto ex = std::max<double>(end.x, b.getMaxX());
	const auto ey = std::max<double>(end.y, b.getMaxY());
	const auto ez = std::max<double>(end.z, b.getMaxZ());
	this->end = Vector3dd(ex, ey, ez);
}

double Box3d::getVolume() const
{
	const auto& length = getLength();
	return length.x * length.y * length.z;
}

bool Box3d::isSame(const Box3d& rhs, const double tolerance) const
{
	return
		start == rhs.getStart() &&
		end == rhs.getEnd();
}
