#pragma once

#include "IShapeScene.h"
#include "WireFrameAttribute.h"

#include "../Math/Line3d.h"
#include "../Shape/WireFrame.h"

#include "LineRenderer.h"

namespace Crystal {
	namespace Scene {

class WireFrameScene : public IShapeScene
{
public:
	WireFrameScene();

	WireFrameScene(const int id, const std::string& name, std::unique_ptr<Shape::WireFrame> shape, const WireFrameAttribute& attribute);

	~WireFrameScene() {};

	WireFrameAttribute getAttribute() const { return attribute; }

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	SceneType getType() const override { return SceneType::WireFrameScene; }

	void onClear() override {}

	Math::Box3d getBoundingBox() const override;

	std::vector<Math::Vector3dd> getAllVertices() const;

	void onBuild(Shader::GLObjectFactory& factory) override;

	void onSend() override;

	void send(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const override;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

	LineRenderer::LineRenderer::GLBuffer getGLBuffer() const { return glBuffer; }

private:
	LineRenderer* renderer;
	LineRenderer::LineRenderer::GLBuffer glBuffer;

	std::unique_ptr<Shape::WireFrame> shape;
	WireFrameAttribute attribute;
};

	}
}