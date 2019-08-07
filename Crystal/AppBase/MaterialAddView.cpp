#include "MaterialAddView.h"

#include "../Graphics/Material.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialAddView::MaterialAddView(const std::string& name, RootScene* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	material("Material"),
	name("Name", "Material1")
{
}

void MaterialAddView::show()
{
	material.show();
	name.show();
	IOkCancelView::show();
}

void MaterialAddView::onOk()
{
	getRepository()->getObjects()->addScene( getRepository()->getObjectFactory()->createMaterialScene(material.getValue(), name.getValue()));
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
