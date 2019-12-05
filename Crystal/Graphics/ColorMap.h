#pragma once

#include <vector>
#include <cassert>
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class ColorMap {
public:
	ColorMap();

	ColorMap(const float min, const float max, const int resolution);

	void setColor(const int index, const Graphics::ColorRGBAf& color);

	int getResolution() const;

	float getNormalized(const float value) const;

	int getIndex(const float value) const;

	Graphics::ColorRGBAf getColorFromIndex(const int i) const;

	Graphics::ColorRGBAf getColor(const float v) const;

	Graphics::ColorRGBAf getInterpolatedColor(const float v) const;

	float getValueFromIndex(const int i) const;

	void setMin(const float m);

	float getMin() const;

	void setMax(const float m);

	float getMax() const;

	void setMinMax(const float min__, const float max__);

	bool isValid();

	std::vector< ColorRGBAf > getColors() const;

private:
	std::vector<ColorRGBAf> colors;

	float min_;
	float max_;
};

	}
}