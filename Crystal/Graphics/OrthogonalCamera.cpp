#include "OrthogonalCamera.h"

#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

using namespace Crystal::Graphics;

glm::mat4 OrthogonalCamera::getProjectionMatrix() const
{
	return glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, near_, far_);
}

