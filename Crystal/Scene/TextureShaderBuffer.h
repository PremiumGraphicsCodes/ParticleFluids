#pragma once

#include <vector>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class TextureScene;

struct TextureShaderBuffer
{
	bool build(Shader::GLObjectFactory& factory);

	void send();

	void release();

	void add(TextureScene* scenes)
	{

	}

private:
	std::vector<TextureScene*> textureObjects;
};

	}
}