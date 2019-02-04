#pragma once

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class DrawableID
{
public:
	DrawableID(const unsigned int id, const unsigned char type)
	{
		this->id = id;
		this->type = type;
	}

	explicit DrawableID(const ColorRGBAf& c)
	{
		fromColor(c);
	}

	explicit DrawableID(const ColorRGBAuc& c)
	{
		fromColor(c);
	}

	void fromColor(const ColorRGBAf& c) {
		ColorRGBAuc uc(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
		fromColor(uc);

	}

	void fromColor(const ColorRGBAuc& c) {
		type = 0;
		id = 0;
		type = c.a;
		id |= c.b;
		id <<= 8;
		id |= c.g;
		id <<= 8;
		id |= c.r;
	}

	ColorRGBAf toColor() const {
		const float red = (id % 256) / 255.0f;
		const float green = ((id / 256) % 256) / 255.0f;
		const float blue = ((id / 256 / 256) % (265 * 256)) / 255.0f;
		const float alpha = getType() / 255.0f;
		return ColorRGBAf(red, green, blue, alpha);
	}

	bool equals(const DrawableID& rhs) const {
		return this->id == rhs.id &&
			this->type == rhs.type;
	}

	bool operator==(const DrawableID& rhs) const { return equals(rhs); }

	bool operator!=(const DrawableID& rhs) const { return !equals(rhs); }

	bool operator<(const DrawableID& rhs) const { return id < rhs.id; }

	bool operator>(const DrawableID& rhs) const { return id > rhs.id; }

	unsigned int getType() const { return type; }

	unsigned int getValue() const { return id; }

private:
	unsigned int id;
	unsigned int type;
};

	}
}