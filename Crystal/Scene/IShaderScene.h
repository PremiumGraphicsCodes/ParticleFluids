#pragma once

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

	//virtual void render(Graphics::ICamera& camera) = 0;

	virtual void render(const Graphics::ICamera& camera) = 0;

private:
	const int id;
	std::string name;
};

	}
}