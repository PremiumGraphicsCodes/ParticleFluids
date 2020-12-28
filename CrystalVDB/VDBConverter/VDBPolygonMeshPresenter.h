#pragma once

#include "../../Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class LineShaderScene;
	}
	namespace VDB {
		class VDBPolygonMesh;

class VDBPolygonMeshPresenter : public Scene::IPresenter
{
public:
	explicit VDBPolygonMeshPresenter(VDBPolygonMesh* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VDBPolygonMesh* model;
	Scene::LineShaderScene* view;
};

	}
}