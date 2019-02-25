#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

		class WFSphereButton : public IPopupButton
		{
		public:
			WFSphereButton(Repository* repository, Canvas* canvas) :
				IPopupButton("Sphere", repository, canvas),
				unum(12),
				vnum(12)
			{
			}

			void onShow() override;

			void onOk() override;

			void onCancel() override
			{

			}

		private:
			int unum;
			int vnum;
			glm::vec3 center = { 0.0f, 0.0f, 0.0f };
			float radius = 1.0;
			glm::vec4 color;
		};

	}
}