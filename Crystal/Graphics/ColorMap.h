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

	Graphics::ColorRGBAf getInterpolatedColor(const float v) const {
		if (v <= min_) {
			return colors.front();// getColor( min_ );
		}
		if (v >= max_) {
			return colors.back();
		}
		const int index1 = getIndex(v);
		const int index2 = getIndex(v) + 1;

		if (index1 < 0) {
			return colors.front();// getColor( min_ );
		}
		if (index2 >= getResolution()) {
			return colors.back();
		}
		const float v1 = getValueFromIndex(index1);
		const float v2 = getValueFromIndex(index2);

		const float ratio = getNormalized(v);

		auto c1 = getColorFromIndex(index1) * (ratio);
		auto c2 = getColorFromIndex(index2) * (1.0f - ratio);
		return c1 + c2;
	}

	float getValueFromIndex(const int i) const {
		const float dt = (max_ - min_) / (getResolution() - 1);
		return (dt * i + min_);
	}

	void setMin(const float m) {
		min_ = m;
		assert(isValid());
	}

	float getMin() const { return min_; }

	void setMax(const float m) {
		max_ = m;
		assert(isValid());
	}

	float getMax() const { return max_; }

	void setMinMax(const float min__, const float max__) {
		this->min_ = min__;
		this->max_ = max__;
		assert(isValid());
	}

	bool isValid() {
		return (min_ <= max_);
	}

	std::vector< ColorRGBAf > getColors() const {
		return colors;
	}

private:
	std::vector<ColorRGBAf> colors;

	float min_;
	float max_;
};

	}
}