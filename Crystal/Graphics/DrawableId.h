#pragma once

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class DrawableID
{
public:
	DrawableID(const unsigned char parentId, const unsigned int childId);

	explicit DrawableID(const ColorRGBAf& c);

	explicit DrawableID(const ColorRGBAuc& c);

	void fromColor(const ColorRGBAf& c);

	void fromColor(const ColorRGBAuc& c);

	ColorRGBAf toColor() const {
		const float red = (childId % 256) / 255.0f;
		const float green = ((childId / 256) % 256) / 255.0f;
		const float blue = ((childId / 256 / 256) % (256 * 256)) / 255.0f;
		const float alpha = getParentId() / 255.0f;
		return ColorRGBAf(red, green, blue, alpha);
	}

	bool equals(const DrawableID& rhs) const {
		return this->childId == rhs.childId &&
			this->parentId == rhs.parentId;
	}

	bool operator==(const DrawableID& rhs) const { return equals(rhs); }

	bool operator!=(const DrawableID& rhs) const { return !equals(rhs); }

	bool operator<(const DrawableID& rhs) const { return childId < rhs.childId; }

	bool operator>(const DrawableID& rhs) const { return childId > rhs.childId; }

	unsigned int getParentId() const { return parentId; }

	unsigned int getChildId() const { return childId; }

private:
	unsigned int parentId;
	unsigned int childId;
};

	}
}