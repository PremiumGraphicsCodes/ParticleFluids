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

ICamera::ICamera(const glm::vec3& eye, const glm::vec3& target, const float near_, const float far_) :
	eye(eye),
	target(target),
	near_(near_),
	far_(far_),
	scale(1.0f),
	rotation(1.0f),
	isOrtho(false)
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

Matrix4df ICamera::getProjectionMatrix() const
{
	if (isOrtho) {
		return glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, near_, far_);
	}
	else {
		return glm::perspective(1.0f, 0.5f * (float)PI, near_, far_);
	}
}


void ICamera::rotate(const float azimuth, const float elevation)
{
	rotation = glm::rotate(rotation, azimuth, getRight());
	rotation = glm::rotate(rotation, elevation, getUp());
}
