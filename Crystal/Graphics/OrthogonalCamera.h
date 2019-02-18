#ifndef __CRYSTAL_GRAPHICS_ORTHOGONAL_CAMERA_H__
#define __CRYSTAL_GRAPHICS_ORTHOGONAL_CAMERA_H__

#include "ICamera.h"
#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

namespace Crystal {
	namespace Graphics {

class OrthogonalCamera : public ICamera
{
public:
	OrthogonalCamera() {}

	glm::mat4 getProjectionMatrix() const override {
		return glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, near_, far_);
	}

private:

};

	}
}

#endif