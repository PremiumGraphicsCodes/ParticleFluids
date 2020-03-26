#pragma once

namespace Crystal {
	namespace Scene {

class IShader
{
public:
	virtual ~IShader() {}

	virtual bool build() = 0;

	virtual void release() = 0;

	virtual void render() = 0;
};

	}
}