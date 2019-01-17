#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

		class CameraMenu : public IMenu
		{
		public:
			CameraMenu(Model* model, Canvas* canvas) :
				IMenu(model, canvas)
			{}

			virtual void show() override;
		};
	}
}