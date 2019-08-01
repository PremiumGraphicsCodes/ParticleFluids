#include "MaterialAddView.h"

#include "../Graphics/Material.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialAddView::MaterialAddView(const std::string& name, RootScene* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	material("Material"),
	name("Name", "Material1")
{
}

void MaterialAddView::show()
{
	material.show();
	name.show();
}

void MaterialAddView::onOk()
{
	getRepository()->getObjects()->addScene( getRepository()->getObjectFactory()->createMaterialScene(material.getValue(), name.getValue()));
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
