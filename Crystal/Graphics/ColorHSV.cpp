#include "ColorHSV.h"

using namespace Crystal::Graphics;

ColorHSV::ColorHSV() :
	h(0.0),
	s(0.0),
	v(0.0)
{}

ColorHSV::ColorHSV(const float h, const float s, const float v) :
	h(h),
	s(s),
	v(v)
{}

ColorRGBAf ColorHSV::toColorRGBA() const
{
	const auto max = v;
	const auto min = max - (s / 1.0f) * max;

	if (0 <= h && h <= 60) {
		const auto g = h / 60.0f * (max - min) + min;
		return ColorRGBAf(max, g, min, 1.0f);
	}
	else if (h <= 120.0f) {
		const auto r = (120.0f - h) / 60.0f * (max - min) + min;
		return ColorRGBAf(r, max, min, 1.0f);
	}
	else if (h <= 180.0f) {
		const auto b = (h - 120.0f) / 60.0f * (max - min) + min;
		return ColorRGBAf(min, max, b, 1.0f);
	}
	else if (h <= 240.0f) {
		const auto g = (240.0f - h) / 60.0f * (max - min) + min;
		return ColorRGBAf(min, g, max, 1.0f);
	}
	else if (h <= 300.0f) {
		const auto r = (h - 240.0f) / 60.0f * (max - min) + min;
		return ColorRGBAf(r, min, max, 1.0f);
	}
	else if (h <= 360.0f) {
		const auto b = (360.0f - h) / 60.0f * (max - min) + min;
		return ColorRGBAf(max, min, b, 1.0f);
	}
	else {
		assert(false);
		return ColorRGBAf(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
