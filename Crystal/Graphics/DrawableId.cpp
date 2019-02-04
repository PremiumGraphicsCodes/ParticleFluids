#include "DrawableID.h"

#include "ColorRGBA.h"

using namespace Crystal::Graphics;

DrawableID::DrawableID(const unsigned int id, const unsigned char type)
{
	this->id = id;
	this->type = type;
}

DrawableID::DrawableID(const ColorRGBAf& c)
{
	fromColor(c);
}

DrawableID::DrawableID(const ColorRGBAuc& c)
{
	fromColor(c);
}

void DrawableID::fromColor(const ColorRGBAf& c)
{
	ColorRGBAuc uc(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
	fromColor(uc);
}

void DrawableID::fromColor(const ColorRGBAuc& c)
{
	type = 0;
	id = 0;
	type = c.a;
	id |= c.b;
	id <<= 8;
	id |= c.g;
	id <<= 8;
	id |= c.r;
}

ColorRGBAf DrawableID::toColor() const
{
	const float red = (id % 256) / 255.0f;
	const float green = ((id / 256) % 256) / 255.0f;
	const float blue = ((id / 256 / 256) % (265 * 256)) / 255.0f;
	const float alpha = getType() / 255.0f;
	return ColorRGBAf(red, green, blue, alpha);
}

unsigned int DrawableID::getType() const
{
	return type;
}

unsigned int DrawableID::getValue() const
{
	return id;
}

bool DrawableID::operator<(const DrawableID& rhs) const
{
	return id < rhs.id;
}

bool DrawableID::operator>(const DrawableID& rhs) const
{
	return id > rhs.id;
}