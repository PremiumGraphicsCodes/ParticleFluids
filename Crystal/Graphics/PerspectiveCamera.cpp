#include "PerspectiveCamera.h"

#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

using namespace Crystal::Graphics;

PerspectiveCamera::PerspectiveCamera() :
	fovy(1.0),
	aspect(1.0)
{}

PerspectiveCamera::PerspectiveCamera(const float fovy, const float aspect) :
	fovy(fovy),
	aspect(aspect)
{}

PerspectiveCamera::PerspectiveCamera(const float fovy, const float aspect, const glm::vec3& target, const glm::vec3& position, const float near_, const float far_) :
	fovy(fovy),
	aspect(aspect),
	ICamera(target, position, near_, far_)
{}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const
{
	return glm::perspective(fovy, aspect, near_, far_);
}
