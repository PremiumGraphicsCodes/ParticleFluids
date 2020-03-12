#pragma once

#include "../Shape/ParticleSystem.h"

#include "IShapeScene.h"
#include "ParticleAttribute.h"

#include "PointRenderer.h"

namespace Crystal {
	namespace Scene {

class ParticleSystemScene : public IShapeScene
{
public:
	ParticleSystemScene();

	ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<Shape::ParticleSystem<ParticleAttribute>> shape);

	~ParticleSystemScene() {};

	Shape::ParticleSystem<ParticleAttribute>* getShape() const { return shape.get(); }

	void onBuild(Shader::GLObjectFactory& factory) override;

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneType::ParticleSystemScene; }

	void onClear() override {};

	void onSend() override;

	void send(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const override;

	Math::Box3d getBoundingBox() const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

	//ParticleAttribute getAttribute() const { return shape->getA}

	void setAttribute(const ParticleAttribute& attribute);

	PointRenderer::GLBuffer getGLBuffer() const { return buffer; }

	void onRender(SceneRenderer* renderer) override;

private:
	PointRenderer::GLBuffer buffer;
	std::unique_ptr< Shape::ParticleSystem<ParticleAttribute> > shape;
};

	}
}