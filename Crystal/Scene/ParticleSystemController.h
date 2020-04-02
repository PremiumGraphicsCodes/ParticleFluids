#pragma once

#include <vector>
#include <memory>

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;
		class PointShader;

class ParticleSystemController
{
public:
	explicit ParticleSystemController(ParticleSystemScene* model);

	void createView(PointShader* renderer);

	void updateView();

private:
	ParticleSystemScene* model;
	std::shared_ptr<PointShaderScene> view;
};

	}
}