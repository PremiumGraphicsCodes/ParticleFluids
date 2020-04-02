#pragma once

#include <vector>
#include <memory>


namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;
		class IShaderScene;
		class SceneShader;

class ParticleSystemController
{
public:
	explicit ParticleSystemController(ParticleSystemScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	PointShaderScene* getView() { return view; }

private:
	ParticleSystemScene* model;
	PointShaderScene* view;
};

	}
}