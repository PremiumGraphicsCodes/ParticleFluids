#pragma once

#include "../Util/UnCopyable.h"

#include "TextureObject.h"
#include "FrameBufferObject.h"
#include "VertexBufferObject.h"
#include "ShaderObject.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Shader {

class GLObjectFactory : private UnCopyable
{
public:
	void clear() {
		textures.clear();
		shaders.clear();
	}


	std::list<FrameBufferObject> fbos;

	std::list<VertexBufferObject> vbos;

	ShaderObject* createShaderObject() {
		auto shader = std::make_unique<ShaderObject>();
		shaders.push_back(std::move(shader));
		return shaders.back().get();
	}

	TextureObject* createTextureObject() {
		auto texture = std::make_unique<TextureObject>();
		texture->create("");
		textures.push_back(std::move(texture));
		return textures.back().get();
	}

private:
	std::list<std::unique_ptr<TextureObject>> textures;
	std::list<std::unique_ptr<ShaderObject>> shaders;
};

	}
}