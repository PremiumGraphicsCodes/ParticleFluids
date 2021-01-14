#pragma once

#include "../../Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace VDB {
		class VDBParticleSystemScene;

class VDBParticleSystemPresenter : public Scene::IPresenter
{
public:
	explicit VDBParticleSystemPresenter(VDBParticleSystemScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VDBParticleSystemScene* model;
	Scene::PointShaderScene* view;
	Scene::PointShaderScene* parentIdView;
	Scene::PointShaderScene* childIdView;
};

	}
}