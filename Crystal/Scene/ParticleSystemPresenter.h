#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;

class ParticleSystemPresenter : public IPresenter
{
public:
	explicit ParticleSystemPresenter(ParticleSystemScene* model);

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