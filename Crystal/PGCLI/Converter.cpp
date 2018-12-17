#include "stdafx.h"
#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"

#include "Converter.h"


using namespace PG::CLI;

Crystal::Math::Vector3df PG::CLI::Converter::toCpp(PG::Core::Math::Vector3d^ src)
{
	return Crystal::Math::Vector3df(src->X, src->Y, src->Z);
}

PG::Core::Math::Vector3d^ PG::CLI::Converter::fromCpp(const Crystal::Math::Vector3df& src)
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
