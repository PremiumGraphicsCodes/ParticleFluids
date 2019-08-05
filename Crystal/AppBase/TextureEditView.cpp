#include "TextureEditView.h"

#include "../Graphics/Material.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TextureEditView::TextureEditView(const std::string& name, RootScene* model, Canvas* canvas) :
	IWindow(name),
	texture("Texture"),
	id("Id"),
	name("Name")
{
	/*
	auto func = [=]()
	{
	};
	editButton.setFunction()
		*/
}

void TextureEditView::show()
{
	id.show();
	name.show();
	texture.show();
}

void TextureEditView::setValue(TextureScene* value)
{
	/*
	texture.setValue(value->getImage());
	id.setValue(value->getId());
	name.setValue(value->getName());
	*/
}
