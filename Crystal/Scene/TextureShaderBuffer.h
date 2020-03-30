#pragma once

#include <vector>

namespace Crystal {
	namespace Scene {
		class TextureScene;

struct TextureShaderBuffer
{
	void build();

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