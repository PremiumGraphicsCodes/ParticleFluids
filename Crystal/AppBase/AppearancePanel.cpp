#include "AppearancePanel.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IntView.h"
#include "StringView.h"
#include "IPopupButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class LightButton : public IPopupButton
	{
	public:
		LightButton(Repository* model, Canvas* canvas) :
			IPopupButton("Light", model, canvas)
		{
		}

		void onShow() override
		{
			ImGui::InputFloat3("Position", &position[0]);
			ImGui::ColorPicker3("Ambient", &ambient[0]);
			ImGui::ColorPicker3("Diffuse", &diffuse[0]);
			ImGui::ColorPicker3("Specular", &specular[0]);
			ImGui::InputText("Name", &name[0], 256);
		}

		void onOk() override
		{
			auto l = new PointLight();
			l->setPosition(position);
			l->setAmbient(ambient);
			l->setDiffuse(diffuse);
			l->setSpecular(specular);
			getModel()->getAppearances()->getLights()->add(l, name);
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
		char name[256];
//		std::stable_partition
	};

	class MaterialButton : public IPopupButton
	{
	public:
		MaterialButton(Repository* model, Canvas* canvas) :
			IPopupButton("Material", model, canvas),
			id("Id", 1),
			name("Name", "Material1")
		{
		}

		void onShow() override
		{
			ImGui::ColorPicker3("Ambient", &ambient[0]);
			ImGui::ColorPicker3("Diffuse", &diffuse[0]);
			ImGui::ColorPicker3("Specular", &specular[0]);
			ImGui::InputFloat("Shininess", &shininess);
			id.show();
			name.show();
		}

		void onOk() override
		{
			Material* m = new Material();
			m->setAmbient(ambient);
			m->setDiffuse(diffuse);
			m->setSpecular(specular);
			m->setShininess(shininess);
			getModel()->getAppearances()->getMaterials()->add(m, name.getValue());
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec4 ambient = { 0,0,0,0 };
		glm::vec4 diffuse = { 0,0,0,0 };
		glm::vec4 specular = { 0,0,0,0 };
		float shininess;
		IntView id;
		StringView name;
	};
}

AppearancePanel::AppearancePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new LightButton(model, canvas) );
	add( new MaterialButton(model, canvas) );
}
