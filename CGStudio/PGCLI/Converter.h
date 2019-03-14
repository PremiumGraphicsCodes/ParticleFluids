#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"

using namespace System;

namespace Crystal {
	namespace UI {
		class Model;
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

	static Crystal::Math::Matrix4dd toCpp(PG::Core::Math::Matrix4d^ src);

	static PG::Core::Math::Matrix4d^ fromCpp(const Crystal::Math::Matrix4dd& src);

	static Crystal::Graphics::ColorRGBAf toCpp(PG::Core::Graphics::ColorRGBA^ src);

	//static PG::Core::Graphics::ColorRGBA fromCpp()
};

	}
}
