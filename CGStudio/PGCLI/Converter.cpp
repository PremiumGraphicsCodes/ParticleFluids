#include "stdafx.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Matrix4d.h"

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

Crystal::Math::Triangle3d PG::CLI::Converter::toCpp(PG::Core::Math::Triangle3d^ src)
{
	const auto& v1 = toCpp(src->v1);
	const auto& v2 = toCpp(src->v2);
	const auto& v3 = toCpp(src->v3);
	return Crystal::Math::Triangle3d({ v1,v2,v3 });
}

PG::Core::Math::Triangle3d^ PG::CLI::Converter::fromCpp(const Crystal::Math::Triangle3d& src)
{
	const auto& vs = src.getVertices();
	auto v0 = fromCpp(vs[0]);
	auto v1 = fromCpp(vs[1]);
	auto v2 = fromCpp(vs[2]);
	return gcnew PG::Core::Math::Triangle3d(v0, v1, v2);
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

Crystal::Math::Matrix4dd PG::CLI::Converter::toCpp(PG::Core::Math::Matrix4d^ src)
{
	return Crystal::Math::Matrix4dd
	(
		src->X00, src->X01, src->X02, src->X03,
		src->X10, src->X11, src->X12, src->X13,
		src->X20, src->X21, src->X22, src->X23,
		src->X30, src->X31, src->X32, src->X33
	);
}

PG::Core::Math::Matrix4d^ PG::CLI::Converter::fromCpp(const Crystal::Math::Matrix4dd& src)
{
	return gcnew PG::Core::Math::Matrix4d
	(
		src[0][0], src[0][1], src[0][2], src[0][3],
		src[1][0], src[1][1], src[1][2], src[1][3],
		src[2][0], src[2][1], src[2][2], src[2][3],
		src[3][0], src[3][1], src[3][2], src[3][3]
	);
}

Crystal::Graphics::ColorRGBAf PG::CLI::Converter::toCpp(PG::Core::Graphics::ColorRGBA^ src)
{
	return Crystal::Graphics::ColorRGBAf(src->R, src->G, src->B, src->A);
}

PG::Core::Graphics::ColorRGBA PG::CLI::Converter::fromCpp(const Crystal::Graphics::ColorRGBAf& src)
{
	auto result = PG::Core::Graphics::ColorRGBA();
	result.R = src.r;
	result.G = src.g;
	result.B = src.b;
	result.A = src.a;
	return result;
}

Crystal::Graphics::PointLight PG::CLI::Converter::toCpp(PG::Core::Graphics::PointLight^ src)
{
	auto result = Crystal::Graphics::PointLight();
	result.setPosition( toCpp( src->Position ) );
	result.setAmbient( toCpp(src->Ambient));
	result.setDiffuse( toCpp(src->Diffuset));
	result.setSpecular(toCpp(src->Specular));
	return result;
}

Crystal::Graphics::Material PG::CLI::Converter::toCpp(PG::Core::Graphics::Material^ src)
{
	auto result = Crystal::Graphics::Material();
	result.ambient = toCpp(src->Ambient);
	result.diffuse = toCpp(src->Diffuse);
	result.specular = toCpp(src->Specular);
	result.shininess = src->Shininess;
	//result.textureId = src->
	return result;
}

Crystal::Math::Box3d PG::CLI::Converter::toCpp(PG::Core::Math::Box3d^ src)
{
	return Crystal::Math::Box3d();
}

Crystal::Scene::SceneType PG::CLI::Converter::toCpp(PG::Core::SceneType src)
{
	switch (src)
	{
	case PG::Core::SceneType::None:
		return Crystal::Scene::SceneType::None;
	case PG::Core::SceneType::Root:
		return Crystal::Scene::SceneType::Root;
	case PG::Core::SceneType::ParticleSystem:
		return Crystal::Scene::SceneType::ParticleSystemScene;
	case PG::Core::SceneType::WireFrame:
		return Crystal::Scene::SceneType::WireFrameScene;
	case PG::Core::SceneType::PolygonMesh:
		return Crystal::Scene::SceneType::PolygonMeshScene;
	case PG::Core::SceneType::PointLight:
		return Crystal::Scene::SceneType::LightScene;
	case PG::Core::SceneType::Material :
		return Crystal::Scene::SceneType::MaterialScene;
	default:
		return Crystal::Scene::SceneType::None;
		break;
	}
}

PG::Core::SceneType PG::CLI::Converter::fromCpp(Crystal::Scene::SceneType src)
{
	switch (src)
	{
	case Crystal::Scene::SceneType::None:
		return PG::Core::SceneType::None;
	case Crystal::Scene::SceneType::Root:
		return PG::Core::SceneType::Root;
	case Crystal::Scene::SceneType::ParticleSystemScene:
		return PG::Core::SceneType::ParticleSystem;
	case Crystal::Scene::SceneType::WireFrameScene:
		return PG::Core::SceneType::WireFrame;
	case Crystal::Scene::SceneType::PolygonMeshScene:
		return PG::Core::SceneType::PolygonMesh;
	case Crystal::Scene::SceneType::LightScene:
		return PG::Core::SceneType::PointLight;
	case Crystal::Scene::SceneType::MaterialScene:
		return PG::Core::SceneType::Material;
	default:
		return PG::Core::SceneType::None;
		break;
	}
}
