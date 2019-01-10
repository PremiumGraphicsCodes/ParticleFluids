#include <stdafx.h>
#include "Camera.h"
#include "../Graphics/PerspectiveCamera.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

PG::CLI::Camera::Camera()
{
	instance = new Crystal::Graphics::PerspectiveCamera(
		1.0,
		0.5f * Tolerance<float>::getPI(),
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		1.0f, 10.0f
	);
}

PG::CLI::Camera::~Camera()
{
	delete instance;
}

void PG::CLI::Camera::Move(PG::Core::Math::Vector3d^ vector)
{
	auto v = Converter::toCpp(vector);
	instance->move(v);
}

void PG::CLI::Camera::MoveTo(PG::Core::Math::Vector3d^ position)
{
	auto p = Converter::toCpp(position);
	instance->moveTo(p);
}

void PG::CLI::Camera::Rotate(double theta, double phi)
{
	instance->rotate(theta, phi);
}

void PG::CLI::Camera::SetRotation(PG::Core::Math::Matrix3d^ matrix)
{
	auto m = Converter::toCpp(matrix);
	instance->setRotation(Crystal::Math::Matrix4dd( m ));
}

void PG::CLI::Camera::Zoom(double s)
{
	instance->zoom(s);
}