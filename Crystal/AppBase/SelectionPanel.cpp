#include "SelectionPanel.h"
#include "../ThirdParty/imgui-1.51/imgui.h"
#include "../Math/Sphere3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../UI/PickUICtrl.h"

#include "IPopupButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class ObjectSelectButton : public IPopupButton
	{
	public:
		ObjectSelectButton(const std::string& name, Repository* model, Canvas* canvas) :
			IPopupButton(name, model, canvas),
			id(0)
		{
		}

		void onShow() override
		{
			ImGui::InputInt("Id", &id);
			if (ImGui::Button("Pick")) {
				auto ctrl = new PickUICtrl(getModel(), getCanvas());
				auto func = [=](int id) {
					return this->id = id;
				};
				ctrl->setFunction(func);
				getCanvas()->setUICtrl(ctrl);
			}
		}

		void onOk() override
		{
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

		int getId() const { return id; }

	private:
		int id;
	};

}


SelectionPanel::SelectionPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add(new ObjectSelectButton("Object", model, canvas));
}
