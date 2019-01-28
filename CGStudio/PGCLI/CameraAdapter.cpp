#include <stdafx.h>
#include "CameraAdapter.h"
#include "../../Crystal/Graphics/PerspectiveCamera.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

PG::CLI::CameraAdapter::CameraAdapter()
{
	instance = new Crystal::Graphics::PerspectiveCamera(
		1.0,
		0.5f * Tolerance<float>::getPI(),
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		1.0f, 10.0f
	);
}

PG::CLI::CameraAdapter::~CameraAdapter()
{
	delete instance;
}

void PG::CLI::CameraAdapter::Move(PG::Core::Math::Vector3d^ vector)
{
	auto v = Converter::toCpp(vector);
	instance->move(v);
}

void PG::CLI::CameraAdapter::MoveTo(PG::Core::Math::Vector3d^ position)
{
	auto p = Converter::toCpp(position);
	instance->moveTo(p);
}

void PG::CLI::CameraAdapter::Rotate(double theta, double phi)
{
	instance->rotate(theta, phi);
}

void PG::CLI::CameraAdapter::SetRotation(PG::Core::Math::Matrix3d^ matrix)
{
	auto m = Converter::toCpp(matrix);
	instance->setRotation(Crystal::Math::Matrix4dd( m ));
}

void PG::CLI::CameraAdapter::Zoom(double s)
{
	instance->zoom(s);
}