#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class IShaderScene
{
public:
	virtual bool build(Shader::GLObjectFactory& glFactory) = 0;

	virtual void release(Shader::GLObjectFactory& glFactory) = 0;

	virtual void render() = 0;
};

	}
}