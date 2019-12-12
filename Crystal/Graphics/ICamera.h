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

	void setEye(const glm::vec3& p);

	void setTarget(const Math::Vector3df& target);

	void lookAt(const Math::Vector3df& eye, const Math::Vector3df& target, const Math::Vector3df& up);

	Math::Vector3df getEye() const { return eye; }

	Math::Matrix4df getModelviewMatrix() const;

	void setFar(const float f) { this->far_ = f; }

	void setNear(const float n) { this->near_ = n; }

	float getFar() const { return far_; }

	float getNear() const { return near_; }

	Math::Matrix4df getProjectionMatrix() const;

	void rotate(const float azimuth, const float elevation);

	void zoom(const float s) { this->scale *= (1.0f + s); }

	Math::Vector3df getRight() const { return rotation * glm::vec4(1, 0, 0, 1); }

	Math::Vector3df getUp() const { return rotation * glm::vec4(0, 1, 0, 1); }

	Math::Vector3df getForward() const { return rotation * glm::vec4(0,0,1,1); }

	Math::Matrix4df getRotationMatrix() const { return rotation; }

	void setRotationMatrix(const Math::Matrix4df& matrix) { this->rotation = matrix; }

private:
	Math::Vector3df eye;
	Math::Vector3df target;
	Math::Matrix4df rotation;
	float near_;
	float far_;
	float scale;
	bool isOrtho;
};

	}
}