#pragma once

#include "ICamera.h"

namespace Crystal {
	namespace Graphics {

class PerspectiveCamera : public ICamera
{
public:
	PerspectiveCamera();

	PerspectiveCamera(const float fovy, const float aspect);

	PerspectiveCamera(const float fovy, const float aspect, const glm::vec3& target, const glm::vec3& position, const float near_, const float far_);

	void setFovy(const float fovy) { this->fovy = fovy; }

	void setAspect(const float aspect) { this->aspect = aspect; }

	glm::mat4 getProjectionMatrix() const override;

private:
	float fovy;
	float aspect;
};

	}
}