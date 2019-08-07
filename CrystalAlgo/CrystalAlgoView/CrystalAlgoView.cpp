#include "../../Crystal/AppBase/Window.h"
#include "../../Crystal/AppBase/FileMenu.h"
#include "../../Crystal/AppBase/CameraMenu.h"
#include "../../Crystal/AppBase/CtrlMenu.h"
#include "../../Crystal/AppBase/ShapeMenu.h"
#include "../../Crystal/AppBase/AppearanceMenu.h"

#include "../../Crystal/AppBase/SceneListPanel.h"

#include "../../Crystal/Scene/RootScene.h"
#include "../../Crystal/UI/Canvas.h"
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

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

namespace {
	class AlgoMenu : public IMenu
	{
	public:
		AlgoMenu(const std::string& name, RootScene* model, Canvas* canvas, ControlPanel* control) :
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


int main(int, char**)
{
	RootScene model;
	Canvas canvas;

	Window window(&model, &canvas);
	if (!window.init()) {
		assert(false);
		return 0;
	}
	auto control = new ControlPanel("Control", &model, &canvas);
	window.add(control);

	window.add(new FileMenu("File", &model, &canvas));
	window.add(new CameraMenu("Camera", &model, &canvas));
	window.add(new CtrlMenu("Ctrl", &model, &canvas));
	window.add(new ShapeMenu("Shape", &model, &canvas, control));
	window.add(new AppearanceMenu("Appearance", &model, &canvas, control));
	window.add(new AlgoMenu("Algo", &model, &canvas, control));

	window.add(new SceneListPanel("Scene", &model, &canvas, control));


	window.show();

	return 0;
}
