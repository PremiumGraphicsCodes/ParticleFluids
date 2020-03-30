#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class IShader
{
public:
	virtual ~IShader() {}

	virtual bool build(Shader::GLObjectFactory& factory) = 0;

	virtual void release() = 0;

	virtual void render() = 0;
};

	}
}