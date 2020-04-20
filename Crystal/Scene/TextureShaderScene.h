#pragma once

#include "IShaderScene.h"

#include "../Shader/TextureObject.h"

#include <vector>

namespace Crystal {
	namespace Graphics {
		class Image;
	}
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class TextureScene;

class TextureShaderScene : public IShaderScene
{
public:
	explicit TextureShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& glFactory);

	void render();

	void send(const Graphics::Image& image);

	Shader::TextureObject* getTextureObject() { return &textureObject; }

private:
	Shader::TextureObject textureObject;
};

	}
}