#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"

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
	static Crystal::Math::Vector3df toCpp(PG::Core::Math::Vector3d^ src);

	static PG::Core::Math::Vector3d^ fromCpp(const Crystal::Math::Vector3df& src);

	static Crystal::Math::Line3dd toCpp(PG::Core::Math::Line3d^ src);

	static PG::Core::Math::Line3d^ fromCpp(const Crystal::Math::Line3dd& src);
};

	}
}
