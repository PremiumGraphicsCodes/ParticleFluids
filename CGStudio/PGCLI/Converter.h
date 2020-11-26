#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Math/Matrix3d.h"
#include "../../Crystal/Math/Matrix4d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Math/Space3d.h"
#include "../../Crystal/Graphics/ColorRGBA.h"
#include "../../Crystal/Graphics/PointLight.h"
#include "../../Crystal/Graphics/Material.h"
#include "../../Crystal/Scene/SceneType.h"
#include "../../Crystal/Shape/Vertex.h"
#include "../../Crystal/Shape/Face.h"
#include "../../Crystal/Scene/WireFrameScene.h"

using namespace System;

namespace PG {
	namespace CLI {

class Converter
{
public:
	static std::string toCpp(System::String^ src);

	static System::String^ fromCpp(const std::string& src);

	static Crystal::Math::Vector2dd toCpp(PG::Core::Math::Vector2d^ src);

	static PG::Core::Math::Vector2d^ fromCpp2d(const Crystal::Math::Vector2dd& src);

	static Crystal::Math::Vector3dd toCpp(PG::Core::Math::Vector3d^ src);

	static PG::Core::Math::Vector3d^ fromCpp(const Crystal::Math::Vector3dd& src);

	static Crystal::Math::Line3dd toCpp(PG::Core::Math::Line3d^ src);

	static PG::Core::Math::Line3d^ fromCpp(const Crystal::Math::Line3dd& src);

	static Crystal::Math::Triangle3d toCpp(PG::Core::Math::Triangle3d^ src);

	static PG::Core::Math::Triangle3d^ fromCpp(const Crystal::Math::Triangle3d& src);

	static Crystal::Math::Sphere3d toCpp(PG::Core::Math::Sphere3d^ src);

	static PG::Core::Math::Sphere3d^ fromCpp(const Crystal::Math::Sphere3d& src);

	static Crystal::Math::Matrix3dd toCpp(PG::Core::Math::Matrix3d^ src);

	static PG::Core::Math::Matrix3d^ fromCpp(const Crystal::Math::Matrix3dd& src);

	static Crystal::Math::Matrix4dd toCpp(PG::Core::Math::Matrix4d^ src);

	static PG::Core::Math::Matrix4d^ fromCpp(const Crystal::Math::Matrix4dd& src);

	static Crystal::Graphics::ColorRGBAf toCpp(PG::Core::Graphics::ColorRGBA^ src);

	static PG::Core::Graphics::ColorRGBA fromCpp(const Crystal::Graphics::ColorRGBAf& src);

	static Crystal::Graphics::PointLight toCpp(PG::Core::Graphics::PointLight^ src);

	static PG::Core::Graphics::PointLight^ fromCpp(const Crystal::Graphics::PointLight& src);

	static Crystal::Graphics::Material toCpp(PG::Core::Graphics::Material^ src);

	static PG::Core::Graphics::Material^ fromCpp(const Crystal::Graphics::Material& src);

	static Crystal::Math::Box3d toCpp(PG::Core::Math::Box3d^ src);

	static PG::Core::Math::Box3d^ fromCpp(const Crystal::Math::Box3d& src);

	static Crystal::Scene::SceneType toCpp(PG::Core::SceneType src);

	static PG::Core::SceneType fromCpp(Crystal::Scene::SceneType src);

	static Crystal::Math::Space3d toCpp(PG::Core::Math::Space3d^ src);

	static Crystal::Math::ISurface3d* toCpp(PG::Core::Math::ISurface3d^ src);

	static Crystal::Math::ISolid3d* toCpp(PG::Core::Math::IVolume3d^ src);

	static Crystal::Shape::Vertex toCpp(PG::Core::Shape::Vertex^ src);

	static Crystal::Shape::Face toCpp(PG::Core::Shape::PolygonFace^ src);

	static Crystal::Shape::WireFrameEdge toCpp(PG::Core::Shape::WireFrameEdge^ src);
};

	}
}
