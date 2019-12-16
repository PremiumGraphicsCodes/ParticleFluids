#include "CameraUICtrl.h"
#include "../Command/Command.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraUICtrl::CameraUICtrl(World* world) :
	prevPosition(0.0f,0.0f),
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

	const auto& matrix = world->getRenderer()->getCamera()->getRotationMatrix();
	const auto v = glm::transpose( Matrix3dd( matrix ) ) * Vector3dd( diff, 0.0);

	Crystal::Command::Command command(CameraTranslateCommandLabels::CameraTranslateCommandLabel);
	Math::Vector3dd t(v.x * scale, v.y * scale, v.z*scale);
	command.setArg(CameraTranslateCommandLabels::TranslateLabel, t);
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

	const auto& matrix = world->getRenderer()->getCamera()->getRotationMatrix();
	const auto v = glm::transpose(Matrix3dd(matrix)) * Vector3dd(diff.y, diff.x, 0.0);
	const auto matrix1 = rotationMatrixX(v.x);
	const auto matrix2 = rotationMatrixY(v.y);
	const auto matrix3 = rotationMatrixZ(v.z);
	command.setArg(CameraRotateCommandLabels::MatrixLabel, matrix3 * matrix2 * matrix1);
	command.execute(world);
	//camera->rotate(diff.y, diff.x);
	this->prevPosition = position;
}

void CameraUICtrl::onWheel(const float dx)
{
	auto camera = world->getRenderer()->getCamera();
	Crystal::Command::Command command(CameraZoomCommandLabels::CameraZoomCommandLabel);
	command.setArg(CameraZoomCommandLabels::ZoomRatioLabel, dx / 100.0f);
	command.execute(world);
}
