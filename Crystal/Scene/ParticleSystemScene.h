#pragma once

#include "../Shape/ParticleSystem.h"

#include "IShapeScene.h"
#include "ParticleAttribute.h"

#include "ParticleSystemPresenter.h"

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public IShapeScene
{
public:
	ParticleSystemScene();

	ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<Shape::ParticleSystem<ParticleAttribute>> shape);

	~ParticleSystemScene() {};

	Shape::ParticleSystem<ParticleAttribute>* getShape() const { return shape.get(); }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::ParticleSystemScene; }

	Math::Box3d getBoundingBox() const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

	void setAttribute(const ParticleAttribute& attribute);

	ParticleSystemPresenter* getPresenter() { return controller.get(); }

private:
	std::unique_ptr< Shape::ParticleSystem<ParticleAttribute> > shape;
	std::unique_ptr< ParticleSystemPresenter > controller;
};

	}
}