#pragma once

#include <vector>
#include <cassert>
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class ColorTable
{
public:
	ColorTable(){}

	explicit ColorTable(const int resolution);

	int getResolution() const;

	void setColor(const int index, const Graphics::ColorRGBAf& color);

	Graphics::ColorRGBAf getColorFromIndex(const int i) const;

	std::vector< ColorRGBAf > getColors() const { return colors; }

private:
	std::vector<ColorRGBAf> colors;
};

class ColorMap
{
public:
	ColorMap();

	ColorMap(const float min, const float max, const ColorTable& table);

	float getNormalized(const float value) const;

	int getIndex(const float value) const;

	Graphics::ColorRGBAf getColor(const float v) const;

	Graphics::ColorRGBAf getInterpolatedColor(const float v) const;

	float getValueFromIndex(const int i) const;

	void setMin(const float m);

	float getMin() const;

	void setMax(const float m);

	float getMax() const;

	void setMinMax(const float min__, const float max__);

	bool isValid();

	ColorTable getTable() const { return table; }

private:
	ColorTable table;

	float min_;
	float max_;
};

	}
}