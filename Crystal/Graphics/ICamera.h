#pragma once

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"


namespace Crystal {
	namespace Graphics {

class ICamera
{
public:
	ICamera();

	ICamera(const glm::vec3& eye, const glm::vec3& target, const float near_, const float far_);

	virtual ~ICamera() = default;

	void moveEye(const glm::vec3& v);

	void moveTarget(const glm::vec3& v);

	void setEye(const glm::vec3& p);

	void setTarget(const Math::Vector3df& target);

	Math::Vector3df getEye() const { return eye; }

	Math::Vector3df getTarget() const { return target; }

	Math::Matrix4df getModelviewMatrix() const;

	void setFar(const float f) { this->far_ = f; }

	void setNear(const float n) { this->near_ = n; }

	float getFar() const { return far_; }

	float getNear() const { return near_; }

	virtual Math::Matrix4df getProjectionMatrix() const = 0;

	void setRotation(const Math::Matrix4df& rotation) { this->rotation = rotation; }

	Math::Matrix4df getRotation() const { return this->rotation; }

	void rotate(const float azimuth, const float elevation);

	void zoom(const float s) { this->scale *= (1.0f + s); }

	Math::Vector3df getRight() const { return rotation * glm::vec4(1, 0, 0, 1); }

	Math::Vector3df getUp() const { return rotation * glm::vec4(0, 1, 0, 1); }

	Math::Vector3df getForward() const { return target - eye; }

	Math::Matrix4df getRotationMatrix() const { return rotation; }

protected:
	Math::Vector3df target;
	Math::Vector3df eye;
	Math::Matrix4df rotation;
	float near_;
	float far_;
	float scale;
};

	}
}