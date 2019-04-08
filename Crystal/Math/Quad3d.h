#pragma once

#include "Vector3d.h"
#include "ICurve3d.h"
#include "Plane3d.h"

namespace Crystal {
	namespace Math {
		class Plane3d;

class Quad3d : ICurve3d
{
public:
	Quad3d(const Vector3dd& origin, const Vector3dd& uvec, const Vector3dd& vvec) :
		origin(origin),
		uvec(uvec),
		vvec(vvec)
	{
	}

	Vector3dd getPosition(const double u, const double v) const override
	{
		return origin + uvec * u + vvec * v;
	}

	Vector3dd getNormal() const
	{
		return glm::normalize( glm::cross(uvec, vvec) );
	}

	bool isInside(const Vector3dd& p) const
	{
		const auto& n = getNormal();

		const auto a = getV0() - p;
		const auto b = getV1() - p;
		const auto c = getV2() - p;
		const auto d = getV3() - p;

		const auto aa = getV1() - getV0();
		const auto bb = getV2() - getV1();
		const auto cc = getV3() - getV2();
		const auto dd = getV0() - getV3();

		const auto& v1 = glm::cross(a, aa);
		if (glm::dot(v1, n) < 0.0) {
			return false;
		}
		const auto& v2 = glm::cross(b, bb);
		if (glm::dot(v2, n) < 0.0) {
			return false;
		}
		const auto& v3 = glm::cross(c, cc);
		if (glm::dot(v3, n) < 0.0) {
			return false;
		}
		return true;

		const auto& v4 = glm::cross(c, dd);
		if (glm::dot(v4, n) < 0.0) {
			return false;
		}
		return true;

	}

	Vector3dd getV0() const { return origin; }

	Vector3dd getV1() const { return origin + uvec; }

	Vector3dd getV2() const { return origin + uvec + vvec; }

	Vector3dd getV3() const { return origin + vvec; }

	Plane3d toPlane() const;

private:
	Vector3dd origin;
	Vector3dd uvec;
	Vector3dd vvec;
};
	}
}