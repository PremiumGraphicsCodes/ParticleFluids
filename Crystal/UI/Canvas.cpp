#include "Canvas.h"
#include "../Graphics/PerspectiveCamera.h"
#include "CameraUICtrl.h"
#include "../Math/Box3d.h"
#include "ObjectRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

Canvas::Canvas(ICamera* camera) :
	camera(camera)
{
	renderer.reset(new Renderer(camera));
}

void Canvas::build()
{
	setUICtrl(new CameraUICtrl(getCamera()));

	renderer->build();
}

void Canvas::render(const int width, const int height)
{
	renderer->render(width, height);
}

void Canvas::onLeftButtonDown(const Vector2df& position)
{
	ctrl->onLeftButtonDown(position);
}

void Canvas::onLeftButtonUp(const Vector2df& position)
{
	ctrl->onLeftButtonUp(position);
}

void Canvas::onRightButtonDown(const Vector2df& position)
{
	ctrl->onRightButtonDown(position);
}

void Canvas::onRightButtonUp(const Vector2df& position)
{
	ctrl->onRightButtonUp(position);
}

void Canvas::onMiddleButtonDown(const Vector2df& position)
{
	ctrl->onMiddleButtonDown(position);
}

void Canvas::onMiddleButtonUp(const Vector2df& position)
{
	ctrl->onMiddleButtonUp(position);
}

void Canvas::onLeftDragging(const Vector2df& position)
{
	ctrl->onLeftDragging(position);
}

void Canvas::onRightDragging(const Vector2df& position)
{
	ctrl->onRightDragging(position);
}

void Canvas::onMiddleDragging(const Vector2df& position)
{
	ctrl->onMiddleDragging(position);
}

void Canvas::onWheel(const float scale)
{
	ctrl->onWheel(scale);
}

void Canvas::fitCamera(const Box3d& boundingBox)
{
	const auto& dist = static_cast<float>( glm::distance(boundingBox.getMin(), boundingBox.getMax()) );
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->setTarget(boundingBox.getCenter());
	camera->moveTo(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0));
}

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
