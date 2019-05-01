#pragma once

#include "../Graphics/Image.h"

namespace Crystal {
	namespace IO {

class ImageFileWriter
{
public:
	enum class ImageFileFormat
	{
		BMP,
		PNG,
		JPG,
	};

	bool write(const std::string& filename, const Graphics::Image& image, const ImageFileFormat format);
private:
};

	}
}