#include "stdafx.h"
#include "../Math/Vector3d.h"

#include "Converter.h"


using namespace PG::CLI;

Crystal::Math::Vector3df Convereter::toCpp(PG::Core::Math::Vector3d^ src)
{
	return Crystal::Math::Vector3df(src->X, src->Y, src->Z);
}

PG::Core::Math::Vector3d^ Convereter::fromCpp(const Crystal::Math::Vector3df& src)
{
	return gcnew PG::Core::Math::Vector3d(src.x, src.y, src.z);
}
