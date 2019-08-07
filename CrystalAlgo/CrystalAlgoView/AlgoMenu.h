#pragma once

#include "../../Crystal/AppBase/IMenu.h"
#include "../../Crystal/AppBase/ControlPanel.h"

#include "IntersectionView.h"
#include "BooleanView.h"
#include "SpaceHashView.h"
#include "MarchingCubesView.h"
#include "VolumeView.h"
#include "VolumeConvertButton.h"
#include "OctreeView.h"
#include "SpaceHashView.h"

#include "../../Crystal/AppBase/imgui.h"

namespace Crystal {
	namespace UI {
		class AlgoMenu : public IMenu
		{
		public:
			AlgoMenu(const std::string& name, Scene::RootScene* model, Canvas* canvas, ControlPanel* control) :
				IMenu(name, model, canvas),
				control(control)
			{
				/*
				add(new SpaceHashView(model, canvas));
				add(new MarchingCubesView(model, canvas));
				add(new VolumeButton(model, canvas));
				add(new VolumeConvertButton(model, canvas));
				add(new SpaceHashView(model, canvas));
				*/
			}

			void show() override
			{
				if (ImGui::BeginMenu("Algo")) {
					if (ImGui::MenuItem("Boolean")) {
						control->setWindow(new BooleanView(getModel(), getCanvas()));
					}
					if (ImGui::MenuItem("SpaceHash")) {
						control->setWindow(new SpaceHashView(getModel(), getCanvas()));
					}
					if (ImGui::MenuItem("Intersection")) {
						control->setWindow(new IntersectionView(getModel(), getCanvas()));
					}
					ImGui::EndMenu();
				}
			}

		private:
			ControlPanel* control;
		};
	}
}
