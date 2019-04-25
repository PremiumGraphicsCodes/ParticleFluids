#pragma once

#include "../Graphics/Image.h"

namespace Crystal {
	namespace IO {

class ImageFileReader
{
public:
	bool read(const std::string& filename);

	Graphics::Image getImage() const { return image; }

private:
	Graphics::Image image;
};

	}
}