#pragma once

namespace Crystal {
	namespace Scene {

class IShaderScene
{
public:
	virtual ~IShaderScene() {}

	virtual bool build() = 0;

	virtual void release() = 0;

	virtual void render() = 0;
};

	}
}