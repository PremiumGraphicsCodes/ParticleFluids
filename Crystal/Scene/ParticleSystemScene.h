#pragma once

#include "IShapeScene.h"
#include "ParticleSystem.h"
#include "ParticleAttribute.h"

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public IShapeScene
{
public:
	ParticleSystemScene() :
		IShapeScene(-1),
		shape(nullptr)
	{}

	ParticleSystemScene(const int id, const std::string& name, ParticleSystem<ParticleAttribute>* shape) :
		IShapeScene(id, name),
		shape(shape)
	{}

	~ParticleSystemScene() {};

	ParticleSystem<ParticleAttribute>* getShape() const { return shape; }

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::ParticleSystemScene; }

	void onClear() override
	{
		delete shape;
	}

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& viewModel) const override;

	virtual void getBoundingBox(Math::Box3d& box) const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

	//ParticleAttribute getAttribute() const { return shape->getA}

	void setAttribute(const ParticleAttribute& attribute);

private:
	ParticleSystem<ParticleAttribute>* shape;
};

	}
}