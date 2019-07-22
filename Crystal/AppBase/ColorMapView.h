#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "TextureView.h"
#include "FloatView.h"
#include "IntView.h"
#include "../Graphics/ColorMap.h"

namespace Crystal {
	namespace UI {

class ColorMapView : public IWindow
{
public:
	ColorMapView(const std::string& name, const Graphics::ColorMap& value) :
		IWindow(name),
		value(value),
		image("Image", Graphics::Image(32,32)),
		resolution("Resolution", value.getResolution()),
		minValue("MinValue", value.getMin()),
		maxValue("MaxValue", value.getMax())
	{
		Graphics::Image img(value.getResolution(), 32);
		for (int i = 0; i < value.getResolution(); ++i) {
			for (int j = 0; j < 32; ++j) {
				const auto color = value.getColorFromIndex(i);
				img.setColor(i,j, Crystal::Graphics::toColorRGBAuc(color));
			}
		}
		image.setValue(img);
	}

	void show() override {
		image.show();
		resolution.show();
		minValue.show();
		maxValue.show();
	}

	//Graphics::ColorRGBAf getValue() const { return Graphics::ColorRGBAf(value[0], value[1], value[2], value[3]); }

	/*
	void setValue(const Graphics::ColorMap& value)
	{
		this->value = value;
		this->resolution.setValue( value.getResolution() );
	}
	*/

private:
	Graphics::ColorMap value;
	TextureView image;
	IntView resolution;
	FloatView minValue;
	FloatView maxValue;
};

	}
}