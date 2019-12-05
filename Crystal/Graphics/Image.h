#pragma once

#include "IImage.h"

namespace Crystal {
	namespace Graphics {

class Image : public IImage
{
public:
	Image()
	{}

	Image(const int width, const int height);

	Image(const int width, const int height, const std::vector< unsigned char >& values);

	Image(const int width, const int height, const unsigned char v);

	static Image White(const int width, const int height);

	static Image Black(const int width, const int height);

	static Image Red(const int width, const int height);

	static Image Green(const int width, const int height);

	static Image Blue(const int width, const int height);

	bool isValid() const;

	void setColor(const int i, const int j, const ColorRGBAuc& c);

	ColorRGBAuc getColor(const int x, const int y) const;

	std::vector<unsigned char> getValues() const { return values; }

	bool equals(const Image& rhs) const;

	bool operator==(const Image& rhs) const { return equals(rhs); }

	bool operator!=(const Image& rhs) const { return !equals(rhs); }

	Image reversed() const;

private:
	std::vector< unsigned char > values;
};

	}
}