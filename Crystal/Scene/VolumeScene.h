#pragma once

#include "../Shape/Volume.h"

#include "IShapeScene.h"
#include <memory>

namespace Crystal {
	namespace Scene {

class VolumeScene : public IShapeScene
{
public:
	VolumeScene(const int id, const std::string& name, std::unique_ptr<Shape::Volume<double>> shape);

	virtual void translate(const Math::Vector3dd& v) { shape->move(v); }

	virtual void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	virtual void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	virtual Math::Vector3dd getPosition(const int index) const { return Math::Vector3dd(0, 0, 0); };

	virtual IShapeScene* clone() const = 0;

	Math::Box3d getBoundingBox() const { return shape->getBoundingBox(); }

	//std::vector<Shape::Particle<double>> toParticles() const;

private:
	std::unique_ptr<Shape::Volume<double>> shape;
};

	}
}