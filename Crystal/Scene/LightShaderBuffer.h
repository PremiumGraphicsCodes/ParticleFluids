#pragma once

#include "IShader.h"

#include "../Graphics/PointLight.h"

#include <vector>

namespace Crystal {
	namespace Scene {

class LightShaderBuffer : public IShader
{
public:
	bool build() override;

	void add(const Graphics::PointLight& l);

	void release() override {}

	void send();

	void render() override {}

	std::vector<Graphics::PointLight> getLights() const { return lights; }

private:
	std::vector<Graphics::PointLight> lights;
};

	}
}