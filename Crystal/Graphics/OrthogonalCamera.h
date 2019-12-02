#pragma once

#include "ICamera.h"
#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

namespace Crystal {
	namespace Graphics {

class OrthogonalCamera : public ICamera
{
public:
	OrthogonalCamera() {}

	glm::mat4 getProjectionMatrix() const override;

private:

};

	}
}
