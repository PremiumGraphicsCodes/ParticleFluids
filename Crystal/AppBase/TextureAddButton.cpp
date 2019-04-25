#include "TextureAddButton.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

TextureAddButton::TextureAddButton(const std::string& name, Repository* model, Canvas* canvas) :
	IPopupButton(name, model, canvas),
	texture("Texture", *model->getShaders()->getTextures(), 0),
	name("Name", "Texture01")
{
}

void TextureAddButton::onShow()
{
	texture.show();
}

void TextureAddButton::onOk()
{
	Image image(32, 32);
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; ++j) {
			image.setColor(i, j, ColorRGBAuc(255, 255, 255, 0));
		}
	}
	getModel()->getShaders()->getTextures()->add(image, name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
