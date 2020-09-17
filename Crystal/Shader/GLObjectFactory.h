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
	void clear();

	std::list<FrameBufferObject> fbos;

	VertexBufferObject* createVertexBufferObject();

	ShaderObject* createShaderObject();

	TextureObject* createTextureObject();

private:
	std::list<std::unique_ptr<VertexBufferObject>> vbos;
	std::list<std::unique_ptr<TextureObject>> textures;
	std::list<std::unique_ptr<ShaderObject>> shaders;
};

	}
}