#pragma once

#include "../Util/UnCopyable.h"

#include "ShaderObjectFactory.h"
#include "TextureObjectFactory.h"
#include "FrameBufferObjectFactory.h"

namespace Crystal {
	namespace Shader {

class GLObjectFactory : private UnCopyable
{
public:
	void clear() {
		shaderFactory.clear();
		textureFactory.clear();
	}

	ShaderObjectFactory* getShaderFactory() { return &shaderFactory; }

	TextureObjectFactory* getTextureFactory() { return &textureFactory; }

	FrameBufferObjectFactory* getFrameBufferFactory() { return &frameBufferFactory; }

private:
	ShaderObjectFactory shaderFactory;
	TextureObjectFactory textureFactory;
	FrameBufferObjectFactory frameBufferFactory;
};

	}
}