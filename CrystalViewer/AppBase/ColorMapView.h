#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "TextureView.h"
#include "FloatView.h"
#include "IntView.h"
#include "../../Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace UI {

class ColorMapView : public IView
{
public:
	ColorMapView(const std::string& name /*, const Graphics::ColorMap& value */);

	void onShow() override;

	//Graphics::ColorRGBAf getValue() const { return Graphics::ColorRGBAf(value[0], value[1], value[2], value[3]); }

	/*
	void setValue(const Graphics::ColorMap& value)
	{
		this->value = value;
		this->resolution.setValue( value.getResolution() );
	}
	*/

	/*
	add(new ColorMapView("ColorMap", colorMap));
	*/

private:
	Graphics::ColorMap value;
	IntView resolution;
	FloatView minValue;
	FloatView maxValue;
};

	}
}