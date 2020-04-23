#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;

class ParticleSystemIdController : public IController
{
public:
	explicit ParticleSystemIdController(ParticleSystemScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	//PointShaderScene* getView() { return view; }

private:
	ParticleSystemScene* model;
	PointShaderScene* parentView;
	PointShaderScene* childView;
};

	}
}