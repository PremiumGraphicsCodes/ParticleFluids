#pragma once

#include <vector>

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;
		class WireFrameScene;
		class LineShaderScene;

class ParticleSystemController
{
public:
	ParticleSystemController();

	void updateBuffer(ParticleSystemScene* src);

private:
	PointShaderScene* view;
};

class WireFrameController
{
private:
	WireFrameScene* model;
	LineShaderScene* view;
};

/*
class SceneController
{

private:
	std::vector<ParticleSystemController> psController;

	//std::map
};
*/
	}
}