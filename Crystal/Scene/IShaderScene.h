#pragma once

#include <list>

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

	void addChild(IShaderScene* child) { children.push_back(child); }

	std::list<IShaderScene*> getChildren() const { return children; }

private:
	std::list<IShaderScene*> children;

};

	}
}