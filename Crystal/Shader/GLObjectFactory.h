#pragma once

#include "../Util/UnCopyable.h"

#include "TextureObjectFactory.h"
#include "FrameBufferObjectFactory.h"

namespace Crystal {
	namespace Shader {

class GLObjectFactory : private UnCopyable
{
public:
	void clear() {
		textureFactory.clear();
		frameBufferFactory.clear();
	}

	TextureObjectFactory* getTextureFactory() { return &textureFactory; }

	FrameBufferObjectFactory* getFrameBufferFactory() { return &frameBufferFactory; }

private:
	TextureObjectFactory textureFactory;
	FrameBufferObjectFactory frameBufferFactory;
};

	}
}