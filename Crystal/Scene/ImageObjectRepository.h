#pragma once

#include "../Util/UnCopyable.h"
#include "ImageObject.h"
#include <vector>

namespace Crystal {
	namespace Model {

class ImageObjectRepository : private UnCopyable
{
public:
	ImageObjectRepository();

	~ImageObjectRepository();

	void clear();

	void add(const Graphics::Image& image, const std::string& name);

	ImageObject* findObjectById(const int id) const;

	std::vector<ImageObject*> getImages() const { return images; }

private:
	std::vector<ImageObject*> images;
	int nextId;
};

	}
}