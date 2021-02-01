
#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/LineShaderScene.h"

namespace Crystal {
	namespace Physics {
		class MeshBoundaryScene;

class MeshBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit MeshBoundaryScenePresenter(MeshBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	MeshBoundaryScene* model;
	Scene::LineShaderScene* view;

	void updateScreenView();

};

	}
}