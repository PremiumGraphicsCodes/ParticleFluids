#pragma once

#include "../Util/UnCopyable.h"

#include "TextureObjectFactory.h"

namespace Crystal {
	namespace Shader {

class GLObjectFactory : private UnCopyable
{
public:
	void clear() {
		textureFactory.clear();
	}

	TextureObjectFactory* getTextureFactory() { return &textureFactory; }

private:
	TextureObjectFactory textureFactory;
};

	}
}