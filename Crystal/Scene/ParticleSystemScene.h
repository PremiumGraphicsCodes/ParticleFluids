#pragma once

#include "../Shape/ParticleSystem.h"

#include "IShapeScene.h"
#include "ParticleAttribute.h"

#include "IParticleSystemScene.h"
#include "IParticleSystemPresenter.h"

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public IParticleSystemScene
{
public:
	ParticleSystemScene();

	ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<Shape::ParticleSystem<ParticleAttribute>> shape);

	~ParticleSystemScene() {};

	Shape::ParticleSystem<ParticleAttribute>* getShape() const { return shape.get(); }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) override { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) override { shape->transform(m); }

	SceneType getType() const override { return SceneTypeLabels::ParticleSystemScene; }

	Math::Box3d getBoundingBox() const override;

	void setAttribute(const ParticleAttribute& attribute);

	std::vector<Math::Vector3dd> getPositions() const override { return shape->getPositions(); }

	IParticleSystemPresenter* getPresenter() { return presenter.get(); }

private:
	std::unique_ptr< Shape::ParticleSystem<ParticleAttribute> > shape;
	std::unique_ptr< IParticleSystemPresenter > presenter;
};

	}
}