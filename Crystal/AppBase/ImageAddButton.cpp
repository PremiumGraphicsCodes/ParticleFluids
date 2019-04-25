#include "ImageAddButton.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

ImageAddButton::ImageAddButton(const std::string& name, Repository* model, Canvas* canvas) :
	IPopupButton(name, model, canvas),
	image("Image", Graphics::Image(256,256,255)),
	name("Name", "Image01")
{
}

void ImageAddButton::onShow()
{
	image.show();
	name.show();
}

void ImageAddButton::onOk()
{
	getModel()->getAppearances()->getImages()->add(image.getValue(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void ImageAddButton::onCancel()
{
}
