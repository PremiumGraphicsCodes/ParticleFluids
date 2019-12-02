#include "OrthogonalCamera.h"

using namespace Crystal::Graphics;

glm::mat4 OrthogonalCamera::getProjectionMatrix() const
{
	return glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, near_, far_);
}

