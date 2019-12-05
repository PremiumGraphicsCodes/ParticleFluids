#include "ColorMap.h"

using namespace Crystal::Graphics;

ColorMap::ColorMap() :
	min_(0.0),
	max_(1.0)
{}

ColorMap::ColorMap(const float min, const float max, const int resolution) :
	min_(min),
	max_(max),
	colors(resolution)
{
}

void ColorMap::setColor(const int index, const ColorRGBAf& color)
{
	colors[index] = color;
}

int ColorMap::getResolution() const
{
	return static_cast<int>(colors.size());
}

float ColorMap::getNormalized(const float value) const
{
	return (value - min_) / (max_ - min_);
}

int ColorMap::getIndex(const float value) const
{
	return static_cast<int>(getNormalized(value) * (getResolution() - 1));
}

ColorRGBAf ColorMap::getColorFromIndex(const int i) const
{
	if (i >= colors.size()) {
		colors.back();
	}
	return colors[i];
}

ColorRGBAf ColorMap::getColor(const float v) const
{
	const int index = getIndex(v);
	return getColorFromIndex(index);
}
