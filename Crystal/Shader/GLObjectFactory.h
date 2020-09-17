#pragma once

#include "../Util/UnCopyable.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Shader {
		class FrameBufferObject;
		class VertexBufferObject;
		class ShaderObject;
		class TextureObject;

class GLObjectFactory : private UnCopyable
{
public:
	void clear();

	FrameBufferObject* createFrameBufferObject();

	VertexBufferObject* createVertexBufferObject();

	ShaderObject* createShaderObject();

	TextureObject* createTextureObject();

private:
	std::list<std::unique_ptr<FrameBufferObject>> fbos;
	std::list<std::unique_ptr<VertexBufferObject>> vbos;
	std::list<std::unique_ptr<TextureObject>> textures;
	std::list<std::unique_ptr<ShaderObject>> shaders;
};

	}
}