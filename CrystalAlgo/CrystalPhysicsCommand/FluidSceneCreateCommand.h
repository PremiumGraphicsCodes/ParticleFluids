#pragma once

#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

		class FluidSceneCreateCommand : public Command::ICommand
		{
			struct Args : Command::IArgs
			{
				Command::Arg<int> sourceParticleSystemId;
				Command::Arg<int> boundaryParticleSystemId;

				Args();
			};

			struct Results : Command::IResults
			{
				Command::Result<int> newId;

				Results() :
					newId("newId", 0)
				{
					add(&newId);
				}
			};

			static std::string getName();

			FluidSceneCreateCommand() :
				ICommand(&args, &results)
			{}

			bool execute(Scene::World* world) override;

		private:
			Args args;
			Results results;
		};
	}
}