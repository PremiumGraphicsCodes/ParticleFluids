#include "Box3d.h"
#include "Sphere3d.h"

#include <numeric>

using namespace Crystal::Math;

Box3d::Box3d() :
	min(0, 0, 0),
	max(1, 1, 1)
{
}

Box3d::Box3d(const Vector3dd& point) :
	min(point),
	max(point)
{}

Box3d::Box3d(const Vector3dd& pointX, const Vector3dd& pointY)
{
	const auto x = std::min<double>(pointX.x, pointY.x);
	const auto y = std::min<double>(pointX.y, pointY.y);
	const auto z = std::min<double>(pointX.z, pointY.z);
	this->min = Vector3dd(x, y, z);
	const auto endX = std::max<double>(pointX.x, pointY.x);
	const auto endY = std::max<double>(pointX.y, pointY.y);
	const auto endZ = std::max<double>(pointX.z, pointY.z);
	this->max = Vector3dd(endX, endY, endZ);
//	assert(isValid());
}

Box3d Box3d::createDegeneratedBox()
{
	Box3d b;
	constexpr auto min = std::numeric_limits<double>::lowest();
	constexpr auto max = std::numeric_limits<double>::max();
	b.max = Vector3dd(min, min, min);
	b.min = Vector3dd(max, max, max);
	return b;
}

bool Box3d::isDegenerated() const
{
	const Box3d b = createDegeneratedBox();
	return b.getMax() == this->getMax() && b.getMin() == this->getMin();
}

void Box3d::add(const Vector3dd& v)
{
	const auto x = std::min<double>(getMinX(), v.x);
	const auto y = std::min<double>(getMinY(), v.y);
	const auto z = std::min<double>(getMinZ(), v.z);
	min = Vector3dd(x, y, z);

	const auto endX = std::max<double>(max.x, v.x);
	const auto endY = std::max<double>(max.y, v.y);
	const auto endZ = std::max<double>(max.z, v.z);
	max = Vector3dd(endX, endY, endZ);
}

void Box3d::add(const Box3d& b)
{
	const auto sx = std::min<double>(getMinX(), b.getMinX());
	const auto sy = std::min<double>(getMinY(), b.getMinY());
	const auto sz = std::min<double>(getMinZ(), b.getMinZ());
	this->min = Vector3dd(sx, sy, sz);

	const auto ex = std::max<double>(max.x, b.getMaxX());
	const auto ey = std::max<double>(max.y, b.getMaxY());
	const auto ez = std::max<double>(max.z, b.getMaxZ());
	this->max = Vector3dd(ex, ey, ez);
}

double Box3d::getVolume() const
{
	const auto& length = getLength();
	return length.x * length.y * length.z;
}

Vector3dd Box3d::getCenter() const
{
	return Vector3dd(
		(getMinX() + max.x) / 2.0,
		(getMinY() + max.y) / 2.0,
		(getMinZ() + max.z) / 2.0
	);
}

bool Box3d::isInside(const Vector3dd& point) const
{
	const bool xIsInterior = (getMinX() < point.x && point.x < max.x);
	const bool yIsInterior = (getMinY() < point.y && point.y < max.y);
	const bool zIsInterior = (getMinZ() < point.z && point.z < max.z);
	return xIsInterior && yIsInterior && zIsInterior;
}


bool Box3d::isSame(const Box3d& rhs, const double tolerance) const
{
	return
		areSame( min, rhs.getStart(), tolerance ) &&
		areSame( max, rhs.getEnd(), tolerance );
}

bool Box3d::hasIntersection(const Box3d& rhs) const
{
	const auto distx = std::fabs(getCenter().x - rhs.getCenter().x);
	const auto lx = getLength().x / 2.0 + rhs.getLength().x / 2.0;

	const auto disty = std::fabs(getCenter().y - rhs.getCenter().y);
	const auto ly = getLength().y / 2.0 + rhs.getLength().y / 2.0;

	const auto distz = std::fabs(getCenter().z - rhs.getCenter().z);
	const auto lz = getLength().z / 2.0 + rhs.getLength().z / 2.0;

	return (distx < lx && disty < ly && distz < lz);
}


Box3d Box3d::getOverlapped(const Box3d& rhs) const
{
	assert(hasIntersection(rhs));
	const auto minx = std::max<double>(this->getStart().x, rhs.getStart().x);
	const auto miny = std::max<double>(this->getStart().y, rhs.getStart().y);
	const auto minz = std::max<double>(this->getStart().z, rhs.getStart().z);

	const auto maxx = std::min<double>(this->getEnd().x, rhs.getEnd().x);
	const auto maxy = std::min<double>(this->getEnd().y, rhs.getEnd().y);
	const auto maxz = std::min<double>(this->getEnd().z, rhs.getEnd().z);

	const Vector3dd min_(minx, miny, minz);
	const Vector3dd max_(maxx, maxy, maxz);
	return Box3d(min_, max_);
}

Vector3dd Box3d::getPosition(const double u, const double v, const double w) const
{
	const auto& length = getLength();
	const auto x = min.x + length.x * u;
	const auto y = min.y + length.y * v;
	const auto z = min.z + length.z * w;
	return Vector3dd(x, y, z);
}

Sphere3d Box3d::getBoundintSphere() const
{
	const auto& halfLength = getLength() * 0.5;
	const auto radius = glm::length(halfLength);
	return Sphere3d(getCenter(), radius);
}

void Box3d::translate(const Math::Vector3dd& v)
{
	this->min += v;
	this->max += v;
}