#pragma once

namespace Crystal {
	namespace Shader {
		class TextureObject;
	}
	namespace Scene {
		class TextureShaderScene;

class ITextureScene
{
public:
	virtual void setTexture(TextureShaderScene* buffer) = 0;

	virtual void sendTexture(const int index, const Shader::TextureObject& texture) = 0;

	virtual void sendAllTextures() = 0;
};

	}
}
