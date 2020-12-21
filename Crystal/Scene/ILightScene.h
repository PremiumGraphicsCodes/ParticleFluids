#pragma once

//#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Graphics {
		class PointLight;
	}
	namespace Scene {
		class LightShaderScene;

class ILightScene
{
public:
	virtual void setLightBuffer(LightShaderScene* buffer) = 0;

	virtual void sendLight(const int index, const Graphics::PointLight& light) = 0;

	virtual void sendAllLights() = 0;
};

	}
}