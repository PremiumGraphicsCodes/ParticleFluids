#include "CameraUICtrl.h"
#include "../Command/Command.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraUICtrl::CameraUICtrl(World* world) :
	world(world)
{
}

void CameraUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
//	camera->move();
}

void CameraUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void CameraUICtrl::onLeftDragging(const Vector2df& position)
{
	auto camera = world->getRenderer()->getCamera();

	const auto diff = prevPosition - position;
	const auto bb = world->getBoundingBox();
	const auto scale = glm::distance(bb.getMin(), bb.getMax()) * 0.1;

	Crystal::Command::Command command("CameraTranslate");
	Math::Vector3dd v(diff.x * scale, diff.y * scale, 0.0);
	command.setArg("Translate", v);
	command.execute(world);

	this->prevPosition = position;
}

void CameraUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void CameraUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void CameraUICtrl::onRightDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	Crystal::Command::Command command(CameraRotateCommandLabels::CameraRotateCommandLabel);
	const auto matrixY = rotationMatrixY(diff.x);
	const auto matrixX = rotationMatrixX(diff.y);
	command.setArg(CameraRotateCommandLabels::MatrixLabel, matrixY * matrixX);
	command.execute(world);
	//camera->rotate(diff.y, diff.x);
	this->prevPosition = position;
}

void CameraUICtrl::onWheel(const float dx)
{
	auto camera = world->getRenderer()->getCamera();
	Crystal::Command::Command command("CameraZoom");
	command.setArg("Ratio", dx / 100.0f);
	command.execute(world);
}
