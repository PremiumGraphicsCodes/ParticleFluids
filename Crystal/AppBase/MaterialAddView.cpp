#include "MaterialAddView.h"

#include "../Graphics/Material.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialAddView::MaterialAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	material("Material"),
	name("Name", "Material1")
{
}

void MaterialAddView::onShow()
{
	material.show();
	name.show();
}

void MaterialAddView::onOk()
{
	getWorld()->getObjects()->addScene( getWorld()->getObjectFactory()->createMaterialScene(material.getValue(), name.getValue()));
	getWorld()->updateViewModel();
}
