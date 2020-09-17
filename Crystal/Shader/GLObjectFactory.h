#pragma once

#include "../Util/UnCopyable.h"

#include "TextureObjectFactory.h"
#include "FrameBufferObject.h"
#include "VertexBufferObject.h"
#include "ShaderObject.h"

#include <list>

namespace Crystal {
	namespace Shader {

class GLObjectFactory : private UnCopyable
{
public:
	void clear() {
		textureFactory.clear();
		shaders.clear();
	}


	TextureObjectFactory* getTextureFactory() { return &textureFactory; }

	std::list<FrameBufferObject> fbos;

	std::list<VertexBufferObject> vbos;

	ShaderObject* createShaderObject() {
		auto shader = std::make_unique<ShaderObject>();
		shaders.push_back(std::move(shader));
		return shaders.back().get();
	}

private:
	TextureObjectFactory textureFactory;
	std::list<std::unique_ptr<ShaderObject>> shaders;
};

	}
}