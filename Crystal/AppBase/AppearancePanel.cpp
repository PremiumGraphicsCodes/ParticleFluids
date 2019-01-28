#include "AppearancePanel.h"
#include "imgui.h"
#include "../UI/Model.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IPopupButton.h"

#include <cereal/cereal.hpp>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class LightButton : public IPopupButton
	{
	public:
		LightButton(Model* model, Canvas* canvas) :
			IPopupButton("Light", model, canvas)
		{
		}

		void onShow() override
		{
			ImGui::InputFloat3("Position", &position[0]);
			ImGui::ColorPicker3("Ambient", &ambient[0]);
			ImGui::ColorPicker3("Diffuse", &diffuse[0]);
			ImGui::ColorPicker3("Specular", &specular[0]);
		}

		void onOk() override
		{
			auto l = new PointLight();
			l->setPosition(position);
			l->setAmbient(ambient);
			l->setDiffuse(diffuse);
			l->setSpecular(specular);
			getModel()->getLights()->add(l);
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 position = { 0,0,0 };
		glm::vec4 ambient = { 0,0,0,0 };
		glm::vec4 diffuse = { 0,0,0,0 };
		glm::vec4 specular = { 0,0,0,0 };

	};
}

void AppearancePanel::show()
{
	ImGui::Begin("Appearance");

	for (auto c : children) {
		c->show();
	}

	ImGui::End();
}

AppearancePanel::AppearancePanel(Model* model, Canvas* canvas) :
	IPanel(model, canvas)
{
	add( new LightButton(model, canvas) );
}
