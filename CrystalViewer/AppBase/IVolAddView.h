#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
#include "ComboBox.h"
#include "BoolView.h"

namespace Crystal {
	namespace UI {

		class IVolAddView : public IOkCancelView
		{
		public:
			IVolAddView(const std::string& name, Scene::World* model, Canvas* canvas);

		protected:
			void addParticleSystem(const std::vector<Math::Vector3dd>& positions);

		private:
			StringView nameView;
			ComboBox presenterView;
			BoolView doBlendView;
		};

	}
}