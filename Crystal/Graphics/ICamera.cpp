#include "ICamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

ICamera::ICamera() :
	near_(1.0f),
	far_(10.0f),
	scale(1.0f),
	rotation(1.0f)
{
}

ICamera::ICamera(const glm::vec3& eye, const glm::vec3& target, const float near_, const float far_) :
	eye(eye),
	target(target),
	near_(near_),
	far_(far_),
	scale(1.0f),
	rotation(1.0f)
{
}

void ICamera::moveEye(const glm::vec3& v)
{
	this->eye += v;
}

void ICamera::moveTarget(const glm::vec3& v)
{
	this->target += v;
}

void ICamera::setEye(const glm::vec3& p)
{
	this->eye = p;
}

void ICamera::setTarget(const Vector3df& target)
{
	this->target = target;
}

Matrix4df ICamera::getModelviewMatrix() const
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), eye);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	return translationMatrix * rotation * scaleMatrix;
}
