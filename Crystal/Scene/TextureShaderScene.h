#pragma once

#include "IShaderScene.h"

#include <vector>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class TextureScene;

class TextureShaderScene : public IShaderScene
{
public:
	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& glFactory);

	virtual void render() = 0;

private:
};

	}
}