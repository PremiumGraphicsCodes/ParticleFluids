#pragma once

namespace Crystal {
	namespace Graphics {
		class PointLight;
	}
	namespace Scene {
		class LightShaderScene;

class ISmoothShaderScene
{
public:
	virtual void setLightBuffer(LightShaderScene* buffer) = 0;

	virtual void sendLight(const int index, const Graphics::PointLight& light) = 0;

	virtual void sendAllLights() = 0;

};
	}
}