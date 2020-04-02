#pragma once

#include <vector>
#include <memory>

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;
		class IShaderScene;
		class SceneShader;

class ParticleSystemController
{
public:
	explicit ParticleSystemController(ParticleSystemScene* model);

	void createView(SceneShader* sceneShader);

	void updateView();

	PointShaderScene* getView() { return view; }

private:
	ParticleSystemScene* model;
	PointShaderScene* view;
};

	}
}