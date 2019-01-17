#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

		class CtrlMenu : public IMenu
		{
		public:
			CtrlMenu(Model* model, Canvas* canvas) :
				IMenu(model, canvas)
			{}

			virtual void show() override;
		};
	}
}