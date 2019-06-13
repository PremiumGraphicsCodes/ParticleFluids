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
		0.5f * PI,
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

void PG::CLI::CameraAdapter::Fit(PG::Core::Math::Box3d^ boundingBox)
{
	/*
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->setTarget(boundingBox.getCenter());
	camera->moveTo(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0));
	*/
}

PG::Core::Math::Matrix4d^ PG::CLI::CameraAdapter::ModelViewMatrix()
{
	return Converter::fromCpp(instance->getModelviewMatrix());
}

PG::Core::Math::Matrix4d^ PG::CLI::CameraAdapter::ProjectionMatrix()
{
	return Converter::fromCpp(instance->getProjectionMatrix());
}


/*
void Canvas::setCameraXY(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->setRotation(glm::mat4());
}

void Canvas::setCameraYZ(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->rotate(glm::radians(90.0f), 0.0);
}

void Canvas::setCameraZX(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->rotate(0.0, glm::radians(90.0f));
}
*/