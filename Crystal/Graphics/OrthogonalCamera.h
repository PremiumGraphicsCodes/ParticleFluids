#pragma once

#include "ICamera.h"

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
