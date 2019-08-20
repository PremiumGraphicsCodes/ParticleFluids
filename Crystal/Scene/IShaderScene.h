#pragma once

#include <list>
#include <string>
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Scene {

class IShaderScene
{
public:
	IShaderScene(const int id, const std::string& name) :
		id(id),
		name(name)
	{}

	virtual ~IShaderScene() {}

	virtual bool build() = 0;

	virtual void render(const Graphics::ICamera& camera) = 0;

	void addChild(IShaderScene* child) { children.push_back(child); }

	std::list<IShaderScene*> getChildren() const { return children; }

private:
	const int id;
	std::string name;
	std::list<IShaderScene*> children;
};

	}
}