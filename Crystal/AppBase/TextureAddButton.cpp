#include "TextureAddButton.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

TextureAddButton::TextureAddButton(const std::string& name, Repository* model, Canvas* canvas) :
	IPopupButton(name, model, canvas),
	texture("Texture", *model->getAppearances()->getTextures(), 0),
	name("Name", "Texture01")
{
}

void TextureAddButton::onShow()
{
	texture.show();
}

void TextureAddButton::onOk()
{
	/*
	Imagef( )
	getModel()->getAppearances()->getTextures()->add(material.getValue().clone(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
	*/
}
