#pragma once

#include "IShapeScene.h"
#include "../Shape/ParticleSystem.h"
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

	ParticleSystemScene(const int id, const std::string& name, Shape::ParticleSystem<ParticleAttribute>* shape) :
		IShapeScene(id, name),
		shape(shape)
	{}

	~ParticleSystemScene() {};

	Shape::ParticleSystem<ParticleAttribute>* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const { return shape == nullptr; }

	SceneType getType() const override { return SceneType::ParticleSystemScene; }

	void onClear() override
	{
		delete shape;
	}

	virtual void addViewModel(UI::SceneViewModel& viewModel) const override;

	virtual void addViewModel(UI::SceneIdViewModel& viewModel) const override;

	virtual void getBoundingBox(Math::Box3d& box) const override;

private:
	Shape::ParticleSystem<ParticleAttribute>* shape;
};

	}
}