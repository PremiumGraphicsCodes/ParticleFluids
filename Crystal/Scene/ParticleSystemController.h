#pragma once

#include <vector>
#include <memory>

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class PointShaderScene;
		class WireFrameScene;
		class LineShaderScene;
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
/*
class SceneController
{

private:
	std::vector<ParticleSystemController> psController;

	//std::map
};
*/