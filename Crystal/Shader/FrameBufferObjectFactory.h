#pragma once

#include "../Util/UnCopyable.h"
#include "FrameBufferObject.h"

#include <list>

namespace Crystal {
	namespace Shader {

class FrameBufferObjectFactory : private UnCopyable
{
public:
	void clear();

	FrameBufferObject* create(const int width, const int height);

	//FrameBufferObject create();

	//FrameBufferObject create(const Graphics::Imagef& image);

private:
	std::list<std::unique_ptr<FrameBufferObject>> buffers;
	//int nextId;

};
	}
}