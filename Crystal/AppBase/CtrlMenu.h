#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

		class CtrlMenu : public IMenu
		{
		public:
			CtrlMenu(const std::string& name, Model* model, Canvas* canvas) :
				IMenu(name, model, canvas)
			{}

			virtual void show() override;
		};
	}
}