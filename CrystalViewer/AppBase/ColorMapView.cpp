#include "ColorMapView.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

ColorMapView::ColorMapView(const std::string& name /*, const ColorMap& value */) :
	IView(name),
	value(value),
	resolution("Resolution", value.getResolution()),
	minValue("MinValue", value.getMin()),
	maxValue("MaxValue", value.getMax())
{
	/*
	Graphics::Image img(value.getResolution(), 32);
	for (int i = 0; i < value.getResolution(); ++i) {
		for (int j = 0; j < 32; ++j) {
			const auto color = value.getColorFromIndex(i);
			img.setColor(i, j, Crystal::Graphics::toColorRGBAuc(color));
		}
	}
	*/

	//ImDrawList* draw_list = ImGui::GetWindowDrawList();
	//draw_list->AddRectFilledMultiColor()
}
