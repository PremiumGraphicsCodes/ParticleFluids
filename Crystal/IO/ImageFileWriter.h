#pragma once

#include "../Graphics/Image.h"

namespace Crystal {
	namespace IO {

class ImageFileWriter
{
public:
	bool write(const std::string& filename, const Graphics::Image& image);
private:
};

	}
}