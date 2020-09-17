#pragma once

#include "../Util/UnCopyable.h"
#include "FrameBufferObject.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Shader {

class FrameBufferObjectFactory : private UnCopyable
{
public:
	FrameBufferObject* create(const int width, const int height);

	void clear() { buffers.clear(); }

	//FrameBufferObject create();

	//FrameBufferObject create(const Graphics::Imagef& image);

private:
	std::vector<std::unique_ptr<FrameBufferObject>> buffers;
	//int nextId;

};
	}
}