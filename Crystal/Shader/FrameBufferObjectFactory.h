#pragma once

#include "../Util/UnCopyable.h"
#include "FrameBufferObject.h"

namespace Crystal {
	namespace Shader {

class FrameBufferObjectFactory : private UnCopyable
{
	void clear() { nextId = 0; }

	FrameBufferObject create();

	//FrameBufferObject create(const Graphics::Imagef& image);

private:
	int nextId;

};
	}
}