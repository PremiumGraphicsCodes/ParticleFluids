#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

		class WireFramePanel : public IPanel
		{
		public:
			WireFramePanel(Model* model, Canvas* canvas) :
				IPanel(model, canvas)
			{}

			void show() override;
		};

	}
}