#include "AppearancePanel.h"
#include "imgui.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/WireFrameBuilder.h"
#include "IntView.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"
#include "Vector3dView.h"
#include "IPopupButton.h"

#include "MaterialAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

namespace {
	class LightButton : public IPopupButton
	{
	public:
		LightButton(Repository* model, Canvas* canvas) :
			IPopupButton("Light", model, canvas),
			position("Position", Vector3dd(0,0,0)),
			ambient("Ambient", glm::vec4(0,0,0,0)),
			diffuse("Diffuse", glm::vec4(0,0,0,0)),
			specular("Specular", glm::vec4(0,0,0,0)),
			name("Name", "Light1")
		{
		}

		void onShow() override
		{
			position.show();
			ambient.show();
			diffuse.show();
			specular.show();
			name.show();
		}

		void onOk() override
		{
			auto l = new PointLight();
			l->setPosition(position.getValue());
			l->setAmbient(ambient.getValue());
			l->setDiffuse(diffuse.getValue());
			l->setSpecular(specular.getValue());
			getModel()->getAppearances()->getLights()->add(l, name.getValue());
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		Vector3dView position;
		Float4View ambient;
		Float4View diffuse;
		Float4View specular;
		StringView name;
	};

}

AppearancePanel::AppearancePanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new LightButton(model, canvas) );
	add( new MaterialAddButton(model, canvas) );
}
