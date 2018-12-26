#include "stdafx.h"
#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"

#include "Converter.h"


using namespace PG::CLI;

Crystal::Math::Vector3dd PG::CLI::Converter::toCpp(PG::Core::Math::Vector3d^ src)
{
	return Crystal::Math::Vector3df(src->X, src->Y, src->Z);
}

PG::Core::Math::Vector3d^ PG::CLI::Converter::fromCpp(const Crystal::Math::Vector3dd& src)
{
	return gcnew PG::Core::Math::Vector3d(src.x, src.y, src.z);
}

Crystal::Math::Line3dd PG::CLI::Converter::toCpp(PG::Core::Math::Line3d^ src)
{
	return Crystal::Math::Line3dd(toCpp(src->Start), toCpp(src->Dir));
}

PG::Core::Math::Line3d^ PG::CLI::Converter::fromCpp(const Crystal::Math::Line3dd& src)
{
	return gcnew PG::Core::Math::Line3d(fromCpp(src.getStart()), fromCpp(src.getEnd()));
}

Crystal::Math::Matrix3dd PG::CLI::Converter::toCpp(PG::Core::Math::Matrix3d^ src)
{
	return Crystal::Math::Matrix3dd
	(
		src->X[0, 0], src->X[0, 1], src->X[0, 2],
		src->X[1, 0], src->X[1, 1], src->X[1, 2],
		src->X[2, 0], src->X[2, 1], src->X[2, 2]
	);
}

PG::Core::Math::Matrix3d^ PG::CLI::Converter::fromCpp(const Crystal::Math::Matrix3dd& src)
{
	return gcnew PG::Core::Math::Matrix3d
	(
		src[0][0], src[0][1], src[0][2],
		src[1][0], src[1][1], src[1][2],
		src[2][0], src[2][1], src[2][2]
	);
}