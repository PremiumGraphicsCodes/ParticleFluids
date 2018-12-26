#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"
#include "../Math/Matrix3d.h"

using namespace System;

namespace Crystal {
	namespace UI {
		class IModel;
	}
}

namespace PG {
	namespace CLI {

class Converter
{
public:
	static Crystal::Math::Vector3dd toCpp(PG::Core::Math::Vector3d^ src);

	static PG::Core::Math::Vector3d^ fromCpp(const Crystal::Math::Vector3dd& src);

	static Crystal::Math::Line3dd toCpp(PG::Core::Math::Line3d^ src);

	static PG::Core::Math::Line3d^ fromCpp(const Crystal::Math::Line3dd& src);

	static Crystal::Math::Matrix3dd toCpp(PG::Core::Math::Matrix3d^ src);

	static PG::Core::Math::Matrix3d^ fromCpp(const Crystal::Math::Matrix3dd& src);
};

	}
}
