#include "TextureAddView.h"

#include "tinyfiledialogs.h"

#include "../IO/ImageFileReader.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::UI;

TextureAddView::TextureAddView(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas),
	image("Image", Graphics::Image(256,256,255)),
	name("Name", "Image01"),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void TextureAddView::show()
{
	image.show();
	name.show();
	if (ImGui::Button("Open")) {
		char const * lFilterPatterns[3] = { "*.bmp", "*.png", "*.jpg" };
		const auto filename = tinyfd_openFileDialog("Open", "", 3, lFilterPatterns, nullptr, 0);
		if (filename != nullptr) {
			ImageFileReader reader;
			if (reader.read(filename)) {
				image.setValue(reader.getImage());
			}
		}
		//canvas->update();
	}
	ok.show();
}

void TextureAddView::onOk()
{
	/*
	getModel()->getAppearances()->getImages()->add(image.getValue(), name.getValue());
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
	*/
}
