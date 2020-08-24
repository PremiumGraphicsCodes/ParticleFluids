#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;

class ParticleSystemController : public IPresenter
{
public:
	explicit ParticleSystemController(ParticleSystemScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	ParticleSystemScene* model;
	PointShaderScene* view;
	PointShaderScene* parentIdView;
	PointShaderScene* childIdView;
};

	}
}