#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../../Crystal/Graphics/PointLight.h"
#include "../../Crystal/Graphics/Material.h"
#include "../../Crystal/Scene/SceneType.h"

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

	static Crystal::Math::Triangle3d toCpp(PG::Core::Math::Triangle3d^ src);

	static PG::Core::Math::Triangle3d^ fromCpp(const Crystal::Math::Triangle3d& src);

	static Crystal::Math::Matrix3dd toCpp(PG::Core::Math::Matrix3d^ src);

	static PG::Core::Math::Matrix3d^ fromCpp(const Crystal::Math::Matrix3dd& src);

	static Crystal::Math::Matrix4dd toCpp(PG::Core::Math::Matrix4d^ src);

	static PG::Core::Math::Matrix4d^ fromCpp(const Crystal::Math::Matrix4dd& src);

	static Crystal::Graphics::ColorRGBAf toCpp(PG::Core::Graphics::ColorRGBA^ src);

	static PG::Core::Graphics::ColorRGBA fromCpp(const Crystal::Graphics::ColorRGBAf& src);

	static Crystal::Graphics::PointLight toCpp(PG::Core::Graphics::PointLight^ src);

	static PG::Core::Graphics::PointLight^ fromCpp(const Crystal::Graphics::PointLight& src);

	static Crystal::Graphics::Material toCpp(PG::Core::Graphics::Material^ src);

	static Crystal::Math::Box3d toCpp(PG::Core::Math::Box3d^ src);

	static Crystal::Scene::SceneType toCpp(PG::Core::SceneType src);

	static PG::Core::SceneType fromCpp(Crystal::Scene::SceneType src);
};

	}
}
