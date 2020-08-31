#pragma once

#include <list>
#include <string>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class IShaderScene
{
public:
	explicit IShaderScene(const std::string& name) :
		name(name)
	{}

	virtual ~IShaderScene() {};

	virtual bool build(Shader::GLObjectFactory& glFactory) = 0;

	virtual void release(Shader::GLObjectFactory& glFactory) = 0;

	virtual void render() = 0;

	std::string getName() const { return name; }

private:
	std::string name;
};

	}
}