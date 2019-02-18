#ifndef __CRYSTAL_GRAPHICS_CAMERA_H__
#define __CRYSTAL_GRAPHICS_CAMERA_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

#include "../ThirdParty/glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

namespace Crystal {
	namespace Graphics {

class ICamera
{
public:
	ICamera() :
		near_(1.0f),
		far_(10.0f),
		scale(1.0f)
	{}

	ICamera(const glm::vec3& eye, const glm::vec3& target, const float near_, const float far_) :
		eye(eye),
		target(target),
		near_(near_),
		far_(far_),
		scale(1.0f)
	{}

	virtual ~ICamera() = default;

	void move(const glm::vec3& v) {
		this->eye += v;
		this->target += v;
	}

	void moveTo(const glm::vec3& p) { this->eye = p; }

	void setTarget(const Math::Vector3df& target) { this->target = target; }

	Math::Vector3df getPosition() const { return eye; }

	Math::Matrix4df getModelviewMatrix() const {
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), eye);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
		return translationMatrix * rotation * scaleMatrix;
	}

	void setFar(const float f) { this->far_ = f; }

	void setNear(const float n) { this->near_ = n; }

	float getFar() const { return far_; }

	float getNear() const { return near_; }

	virtual Math::Matrix4df getProjectionMatrix() const = 0;

	void setRotation(const Math::Matrix4df& rotation) { this->rotation = rotation; }

	void rotate(const float azimuth, const float elevation) {
		rotation = glm::rotate(rotation, azimuth, getRight());
		rotation = glm::rotate(rotation, elevation, getUp());
	}

	void zoom(const float s) { this->scale *= (1.0f + s); }

	Math::Vector3df getRight() const { return rotation * glm::vec4(1, 0, 0, 1); }

	Math::Vector3df getUp() const { return rotation * glm::vec4(0, 1, 0, 1); }

	Math::Vector3df getForward() const { return target - eye; }

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

#endif