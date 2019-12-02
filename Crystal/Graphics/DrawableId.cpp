#include "DrawableId.h"

using namespace Crystal::Graphics;

DrawableID::DrawableID(const unsigned char parentId, const unsigned int childId)
{
	this->parentId = parentId;
	this->childId = childId;
}

DrawableID::DrawableID(const ColorRGBAf& c)
{
	fromColor(c);
}

DrawableID::DrawableID(const ColorRGBAuc& c)
{
	fromColor(c);
}

void DrawableID::fromColor(const ColorRGBAf& c) {
	ColorRGBAuc uc(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
	fromColor(uc);
}

void DrawableID::fromColor(const ColorRGBAuc& c) {
	parentId = 0;
	childId = 0;
	parentId = c.a;
	childId |= c.b;
	childId <<= 8;
	childId |= c.g;
	childId <<= 8;
	childId |= c.r;
}
