#pragma once

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class DrawableID
{
public:
	DrawableID(const unsigned int id, const unsigned char type);

	explicit DrawableID(const ColorRGBAf& c);

	explicit DrawableID(const ColorRGBAuc& c);

	void fromColor(const ColorRGBAf& c);

	void fromColor(const ColorRGBAuc& c);

	ColorRGBAf toColor() const;

	bool equals(const DrawableID& rhs) const {
		return this->id == rhs.id &&
			this->type == rhs.type;
	}

	bool operator==(const DrawableID& rhs) const { return equals(rhs); }

	bool operator!=(const DrawableID& rhs) const { return !equals(rhs); }

	bool operator<(const DrawableID& rhs) const;

	bool operator>(const DrawableID& rhs) const;

	unsigned int getType() const;

	unsigned int getValue() const;

private:
	unsigned int id;
	unsigned int type;
};

	}
}