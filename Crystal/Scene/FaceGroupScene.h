#pragma once

#include "IScene.h"
#include "../Shape/Face.h"
#include "SmoothRenderer.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class MaterialScene;

class FaceGroupScene : public IScene
{
public:
	FaceGroupScene(const int id, const std::string& name, PolygonMeshScene* polygonMesh);

	void addFace(Shape::Face f) { this->faces.push_back(f); }

	std::vector<Shape::Face> getFaces() const { return faces; }

	void setMaterial(MaterialScene* material);

	MaterialScene* getMaterial() const { return material; }

	SceneType getType() const override { return SceneType::FaceGroupScene; }

	void onBuild(Shader::GLObjectFactory& factory) override;

	void onSend() override;

	//void toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const;

	void onClear() override {
		faces.clear();
	}

	SmoothRenderer::GLBuffer getGLBuffer() const { return glBuffer; }

private:
	PolygonMeshScene* polygonMesh;
	MaterialScene* material;
	std::vector<Shape::Face> faces;
	SmoothRenderer::GLBuffer glBuffer;

};

	}
}