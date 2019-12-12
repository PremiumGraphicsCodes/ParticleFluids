#include "ICamera.h"

#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

ICamera::ICamera() :
	near_(1.0f),
	far_(10.0f),
	scale(1.0f),
	rotation(1.0f),
	isOrtho(false)
{
}

ICamera::ICamera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, const float near_, const float far_) :
	near_(near_),
	far_(far_),
	scale(1.0f),
	rotation(1.0f),
	isOrtho(false)
{
	lookAt(eye, target, up);
}

void ICamera::moveEye(const glm::vec3& v)
{
	this->eye += v;
	this->rotation = glm::lookAt(eye, target, up);
}

void ICamera::setEye(const glm::vec3& p)
{
	this->eye = p;
	this->rotation = glm::lookAt(eye, target, up);
}

void ICamera::setTarget(const Vector3df& target)
{
	this->target = target;
	this->rotation = glm::lookAt(eye, target, up);
}

void ICamera::lookAt(const Vector3df& eye, const Vector3df& target, const Vector3df& up)
{
	this->eye = eye;
	this->target = target;
	this->up = up;
	this->rotation = glm::lookAt(eye, target, up);
}

Matrix4df ICamera::getModelViewMatrix() const
{
	//glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), eye);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	return rotation * scaleMatrix;
}

Matrix4df ICamera::getProjectionMatrix() const
{
	if (isOrtho) {
		return glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, near_, far_);
	}
	else {
		return glm::perspective(1.0f, 0.5f * (float)PI, near_, far_);
	}
}

Vector3df ICamera::getRight() const
{
	const auto& f = getForward();
	return glm::cross(up, f);
}

Vector3df ICamera::getUp() const
{
	return up;
}

Vector3df ICamera::getForward() const
{
	return glm::normalize(target - eye);
}
